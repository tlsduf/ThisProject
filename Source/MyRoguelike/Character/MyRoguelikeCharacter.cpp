// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyRoguelikeCharacter.h"
#include "../Core/MyRoguelikeGameMode.h"
#include "../Skill/Skillbase.h"
#include "../Common/GameLog.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include <GameFramework/Controller.h>
#include <GameFramework/PlayerController.h>

#include <TimerManager.h>
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Engine/DamageEvents.h>



#include UE_INLINE_GENERATED_CPP_BY_NAME(MyRoguelikeCharacter)

AMyRoguelikeCharacter::AMyRoguelikeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;			 // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;		// The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;								// Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AMyRoguelikeCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 게임시작시 기본체력초기화
	Health = MaxHealth;
}

// Called every frame
void AMyRoguelikeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 뛰는 상태인지 판별하여 MaxWalkSpeed 초기화.
	if (IsJog && IsWPressed)
	{
		GetCharacterMovement()->MaxWalkSpeed = ThisJogSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = ThisSpeed;
		IsJog = false;
	}

	// 줌을 해도 되는지 판별
	if (CanZoom)
	{
		ZoomInOut(DeltaTime);
	}

	// 전투상태인지 판별하고, 전투상태라면 줌아웃
	if (InCombat)
	{
		if (IsZoomed)
		{
			SetZoomOutProp();
		}
		RotatePawn(DeltaTime);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyRoguelikeCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// =============================================================
// SkillInfos의 TSubClassOf들을 설정된 순서대로 Skills 배열에 인스턴스화 시킵니다.
// =============================================================
void AMyRoguelikeCharacter::InitSkills()
{
	Skills.Empty();
	for (const auto &skillInfo : SkillInfos)
	{
		Skills.Add(NewObject<USkillBase>(this, skillInfo));
	}
}

void AMyRoguelikeCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}
void AMyRoguelikeCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AMyRoguelikeCharacter::Move(const FInputActionValue &Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		if (InCombat)
		{
			SetActorRotation(YawRotation);
		}
	}
}
void AMyRoguelikeCharacter::Look(const FInputActionValue &Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr && CanCameraControl)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// =============================================================
// 아래부터 각 상황에 맞는 스킬 호출 함수입니다. PlayerController에서 호출하면, 받아온 Index대로
// 인스턴스화 된 배열의 스킬에서 상황에 맞는 함수를 호출합니다.
// =============================================================
void AMyRoguelikeCharacter::SkillStarted(const uint8 &InSkillIndex)
{
	if (InSkillIndex < Skills.Num())
	{
		Skills[InSkillIndex]->SkillStarted();
	}
}
void AMyRoguelikeCharacter::SkillOngoing(const uint8 &InSkillIndex)
{
	if (InSkillIndex < Skills.Num())
	{
		Skills[InSkillIndex]->SkillOngoing();
	}
}
void AMyRoguelikeCharacter::SkillTriggered(const uint8 &InSkillIndex)
{
	if (InSkillIndex < Skills.Num())
	{
		Skills[InSkillIndex]->SkillTriggered();
	}
}
void AMyRoguelikeCharacter::SkillCompleted(const uint8 &InSkillIndex)
{
	if (InSkillIndex < Skills.Num())
	{
		Skills[InSkillIndex]->SkillCompleted();
	}
}
void AMyRoguelikeCharacter::SkillCanceled(const uint8 &InSkillIndex)
{
	if (InSkillIndex < Skills.Num())
	{
		Skills[InSkillIndex]->SkillCanceled();
	}
}

// Debug #BP on/off
void AMyRoguelikeCharacter::DebugActorRotation()
{
	const FRotator Rotation = GetActorRotation();
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + Rotation.Vector() * 300;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, 0, -1);
	DrawDebugDirectionalArrow(GetWorld(),
							  Start - Rotation.Vector() * 150,
							  Start + Rotation.Vector() * 150,
							  120.f,
							  FColor::Red,
							  0,
							  -1.f,
							  0,
							  3.f);
}

//================================================================
// 줌인아웃 함수 // 변수값은 protected 이므로 에이밍, 특수스킬 뷰 변경 등에 활용가능하다.
//================================================================
void AMyRoguelikeCharacter::SetZoomInProp()
{
	if (!IsZoomed && !InCombat)
	{
		MyTargetArmLength = 250.0f;
		MyTargetArmLocation = FVector(0, 0, 0);
		MyCameraLocation = FVector(0, 0, 0);

		IsZoomed = true;
		ZoomInterpTime = 6;
		CanZoom = true;
	}
}
void AMyRoguelikeCharacter::SetZoomOutProp()
{
	if (IsZoomed)
	{
		MyTargetArmLength = 400.0f;
		MyTargetArmLocation = FVector(0, 0, 55);
		MyCameraLocation = FVector(0, 0, 55);

		IsZoomed = false;
		ZoomInterpTime = 6;
		CanZoom = true;
	}
}
void AMyRoguelikeCharacter::ZoomInOut(float DeltaTime)
{
	CameraBoom->TargetArmLength = FMath::FInterpTo(
		CameraBoom->TargetArmLength,
		MyTargetArmLength,
		DeltaTime,
		ZoomInterpTime);
	CameraBoom->SetRelativeLocation(FMath::VInterpTo(
		CameraBoom->GetRelativeLocation(),
		MyTargetArmLocation,
		DeltaTime,
		ZoomInterpTime));
	FollowCamera->SetRelativeLocation(FMath::VInterpTo(
		FollowCamera->GetRelativeLocation(),
		MyCameraLocation,
		DeltaTime,
		ZoomInterpTime));
	if (CameraBoom->TargetArmLength == MyTargetArmLength)
	{
		CanZoom = false; // 줌인아웃이 완료되면 함수실행중지
	}
}

//================================================================
// 폰 회전 함수 // 전투상태일 때만 자동회전. Tick에서 구현
//================================================================
void AMyRoguelikeCharacter::RotatePawn(float DeltaTime)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	SetActorRotation(FMath::RInterpTo(
		GetActorRotation(),
		YawRotation,
		DeltaTime,
		10));
}

// Base Movement
// TODO 속도함수 맹글기
void AMyRoguelikeCharacter::SetThisSpeed(float Speed)
{
	ThisSpeed = Speed;
}
void AMyRoguelikeCharacter::SetThisJogSpeed(float JogSpeed)
{
	ThisJogSpeed = JogSpeed;
}
void AMyRoguelikeCharacter::CalculateSpeed()
{
	// ThisSpeed = DefaultSpeed + DefaultSpeed * (ItemVar * ItemCoff + OtherItemVar * OtherItemCoff);
}

//================================================================
// Jog //W가 눌린 상태일때만 뛸 수 있음 //W 때면 jog중지
//================================================================
void AMyRoguelikeCharacter::Jog()
{
	if (!IsJog && IsWPressed && CanJog)
	{
		IsJog = true;
		SetZoomOutProp();
		SetInCombatFalse();
	}
	else if (IsJog)
	{
		IsJog = false;
	}
}
void AMyRoguelikeCharacter::WPressed()
{
	IsWPressed = true;
}
void AMyRoguelikeCharacter::WReleased()
{
	IsWPressed = false;
}

//================================================================
// 데미지 받는 함수
//================================================================
// TakeDamageHandle
float AMyRoguelikeCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	// DamageImmunity가 false 일 때 데미지계산
	if (!DamageImmunity && EventInstigator != Controller)
	{
		HandleCombatState();
		float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

		//================================================================
		// 1.데미지이벤트 판별
		//================================================================
		
		if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
		{
			UE_LOG(LogTemp, Warning, TEXT("Taken Point Damage"));
			LOG_SCREEN(TEXT("Taken Point Damage"));
			const FPointDamageEvent *PointDamageEvent = static_cast<const FPointDamageEvent *>(&DamageEvent);
			if (0 == (PointDamageEvent->HitInfo.BoneName).Compare(FName(TEXT("Head"))))
			{
				// TODO 부위별 데미지 기능 실현
				Damage *= 5;
			}
		}
		else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
		{
			UE_LOG(LogTemp, Warning, TEXT("Taken Radial Damage"));
			LOG_SCREEN(TEXT("Taken Radial Damage"));
			const FRadialDamageEvent *RadialDamageEvent = static_cast<const FRadialDamageEvent *>(&DamageEvent);
		}

		//================================================================
		// 2.데미지 계산(공식적용-올림내림)
		//================================================================
		// TODO 방어력, 공격효과 적용해서 데미지공식 적용하기
		// TODO 효과적용 방식 : 체력비례피해(최대or현재), 고정피해(방어구관통), 지속피해(틱뎀), 방어력감소(영구or시간), 폭발스택
		Damage = Damage * (100 / 100 + Armor);
		Damage = (int)(Damage + 0.2); // 데미지 소수점 처리 *소수점첫째자리가 0.8 이상이면 올림, 미만시 내림
		DamageText = Damage;		  // 데미지전역변수에 값 전달

		Damage = FMath::Min(Health, Damage);
		Health -= Damage;

		//================================================================
		// 3.애니메이션 플레이 //bool 변수로 0.3초마다 애니메이션 실행
		//================================================================
		if (CanTakeDamageAnim)
		{
			TakeDamageAnim = true;
			GetWorldTimerManager().SetTimerForNextTick(this, &AMyRoguelikeCharacter::SetTakeDamageAnimFalse);
			CanTakeDamageAnim = false;
			GetWorldTimerManager().SetTimer(TakeDamageHandle, this, &AMyRoguelikeCharacter::SetCanTakeDamageAnimTrue, 0.3f, false);
		}

		//================================================================
		// 4.죽음구현
		//================================================================
		if (IsDead())
		{
			UE_LOG(LogTemp, Warning, TEXT("He Died"));
			LOG_SCREEN(TEXT("He Died"));
			AMyRoguelikeGameMode *GameMode = GetWorld()->GetAuthGameMode<AMyRoguelikeGameMode>();
			if (GameMode != nullptr)
			{
				GameMode->PawnKilled(this);
			}

			// 20초 뒤 액터 destroy
			GetWorldTimerManager().SetTimer(
				TakeDamageHandle, [this]()
				{ Destroy(); },
				20.0f, false);
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 캡슐콜리전 무효
		}

		UE_LOG(LogTemp, Warning, TEXT("Now Health : %f"), Health);
		LOG_SCREEN(TEXT("Now Health : %f"), Health);
		return Damage;
	}
	else // DamageImmunity가 true 일 때 Damage = 0
	{
		HandleCombatState();
		float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		Damage = 0.f;

		// 애니메이션 플레이 //bool 변수로 0.3초마다 애니메이션 실행
		if (CanTakeDamageAnim)
		{
			TakeDamageAnim = true;
			GetWorldTimerManager().SetTimerForNextTick(this, &AMyRoguelikeCharacter::SetTakeDamageAnimFalse);
			CanTakeDamageAnim = false;
			GetWorldTimerManager().SetTimer(TakeDamageHandle, this, &AMyRoguelikeCharacter::SetCanTakeDamageAnimTrue, 0.3f, false);
		}

		return Damage;
	}
}
void AMyRoguelikeCharacter::SetTakeDamageAnimFalse()
{
	TakeDamageAnim = false;
}
void AMyRoguelikeCharacter::SetCanTakeDamageAnimTrue()
{
	CanTakeDamageAnim = true;
}

//================================================================
// 전투상태 핸들링 함수 // 전투상태 돌입 5초 후, 전투상태 자동 해제. // 해제 전 갱신 시, 5초갱신.
//================================================================
void AMyRoguelikeCharacter::HandleCombatState()
{
	// InCombat을 true로 설정합니다.
	InCombat = true;

	// 만약 타이머가 이미 실행 중이면, 타이머를 초기화하고 5초 후에 다시 호출합니다.
	if (GetWorldTimerManager().IsTimerActive(CombatStateTHandle))
	{
		GetWorldTimerManager().ClearTimer(CombatStateTHandle);
		GetWorldTimerManager().SetTimer(CombatStateTHandle, this, &AMyRoguelikeCharacter::SetInCombatFalse, 5.f, false);
	}
	else
	{
		// 타이머가 실행 중이 아니면, 5초 후에 InCombat을 false로 설정합니다.
		GetWorldTimerManager().SetTimer(CombatStateTHandle, this, &AMyRoguelikeCharacter::SetInCombatFalse, 5.f, false);
	}
}
void AMyRoguelikeCharacter::SetInCombatFalse()
{
	InCombat = false;
}

bool AMyRoguelikeCharacter::GetCombatState()
{
	return InCombat;
}

// ufunction 으로 임시 anim 재생
bool AMyRoguelikeCharacter::IsDead() const
{
	return Health <= 0;
}

float AMyRoguelikeCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

float AMyRoguelikeCharacter::GetDamage() const
{
	return DamageText;
}