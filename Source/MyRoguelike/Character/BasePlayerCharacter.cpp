// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerCharacter.h"
#include "../Skill/BaseHitscan.h"
#include "../Skill/ProjectileGranade.h"
#include "../Skill/ProjectileMissile.h"
#include "../Skill/BaseMelee.h"

#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include <Components/InputComponent.h>
#include <GameFramework/Controller.h>
#include <GameFramework/PlayerController.h>

#include <TimerManager.h>
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

#include UE_INLINE_GENERATED_CPP_BY_NAME(BasePlayerCharacter)

void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	BaseHitscan = GetWorld()->SpawnActor<ABaseHitscan>(BaseHitscanClass);
	BaseHitscan->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_r"));
	BaseHitscan->SetOwner(this);

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//  뛰는 상태인지 판별하여 추가조건 실행
	if (IsJog && IsWPressed)
	{
		// 뛰는 상태라면 언에임
		UnAiming();
	}

	if (IsRunningRM)
	{
		// 조준상태에서는 카메라 방향 = 폰 방향
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		HandleCombatState();
		SetActorRotation(YawRotation);
	}

	if (IsRunningQ)
	{
		HandleCombatState();
		CanJog = false;

		CanRM = false;
		CanE = false;
		CanR = false;
	}

	if (IsRunningE)
	{
		HandleCombatState();
		CanJog = false;

		CanDash = false;
		CanRM = false;
		CanLM = false;
		CanQ = false;
		CanR = false;
	}

	if (IsRunningR)
	{
		HandleCombatState();
		CanJog = false;

		CanRM = false;
		CanQ = false;
		CanE = false;
	}

	if (DebugOnOff)
	{
		//*마우스포인트
		DrawDebugSphere(GetWorld(), GetUnderCursorLocation().ImpactPoint, 32, 16, FColor::Red, false, -1.f);
		DrawDebugSphere(GetWorld(), GetUnderCursorLocation().ImpactPoint, 256, 64, FColor::Blue, false, -1.f); // 파란 디버그구

		//*라인트레이스
		BaseHitscan->DebugLineTraceTick();

		//*폰방향
		DebugActorRotation();

		//*R디버그구
		FVector Granade_socketLocation = GetMesh()->GetSocketLocation("Granade_socket");
		DrawDebugSphere(GetWorld(), Granade_socketLocation, 16, 16, FColor::Red, false, -1.f);
	}

	if (DrawERange)
	{
		//*스킬e 범위 디버그
		DrawDebugSphere(GetWorld(), GetUnderCursorLocation().ImpactPoint, 32, 16, FColor::Red, false, -1.f);
		DrawDebugSphere(GetWorld(), GetUnderCursorLocation().ImpactPoint, 500, 64, FColor::Blue, false, -1.f); // 파란 디버그구
	}
}

void ABasePlayerCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftShift", IE_Pressed, this, &ABasePlayerCharacter::Dash);
	PlayerInputComponent->BindAction("LeftMouse", IE_Pressed, this, &ABasePlayerCharacter::CombatLM);
	PlayerInputComponent->BindAction("LeftMouse", IE_Released, this, &ABasePlayerCharacter::CombatLMReleased);
	PlayerInputComponent->BindAction("RightMouse", IE_Pressed, this, &ABasePlayerCharacter::Aiming);
	PlayerInputComponent->BindAction("RightMouse", IE_Released, this, &ABasePlayerCharacter::UnAiming);
	PlayerInputComponent->BindAction("Q", IE_Pressed, this, &ABasePlayerCharacter::CombatQ);
	PlayerInputComponent->BindAction("E", IE_Pressed, this, &ABasePlayerCharacter::CombatE);
	PlayerInputComponent->BindAction("R", IE_Pressed, this, &ABasePlayerCharacter::CombatR);
}

// Movement
void ABasePlayerCharacter::Dash()
{
	const FVector CurrentAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
	float CurrentAccelLength = CurrentAcceleration.SizeSquared();
	if ((Controller != nullptr) && !IsDash && CanDash && !IsCooldownDash && CurrentAccelLength > 0)
	{
		// const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Rotation = GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		LaunchCharacter(CurrentAcceleration.GetSafeNormal() * DashDistance, true, true);
		// GetCharacterMovement()->MaxWalkSpeed = DashDistance;

		UParticleSystemComponent *ParticleSystemComponent = UGameplayStatics::SpawnEmitterAttached(DashEffect, GetRootComponent());

		//*후행 조건 설정부
		IsDash = true;
		CanDash = false;
		IsCooldownDash = true;

		UnAiming();

		SetZoomOutProp();

		GetWorldTimerManager().SetTimer(DashTHandle, this, &ABasePlayerCharacter::StopDashing, DashingTime, false);
	}
}
void ABasePlayerCharacter::StopDashing()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetWorldTimerManager().SetTimer(DashTHandle, this, &ABasePlayerCharacter::ResetDash, 0.2f, false);
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
}
void ABasePlayerCharacter::ResetDash()
{
	IsDash = false;
	CanDash = true;
	SetInCombatFalse();
	IsJog = true;

	GetWorldTimerManager().SetTimer(DashTHandle, this, &ABasePlayerCharacter::ResetCooldownDash, CooldownTimeLShift, false);
}
void ABasePlayerCharacter::ResetCooldownDash()
{
	IsCooldownDash = false;
}

// (skill LM)
void ABasePlayerCharacter::CombatLM()
{
	if (!IsRunningLM && CanLM)
	{
		CombatLMFire();
		CanLM = false;
		IsRunningLM = true;
		GetWorldTimerManager().SetTimer(LMFireTHandle, this, &ABasePlayerCharacter::CombatLMFire, FireRate, true);
	}
}
void ABasePlayerCharacter::CombatLMReleased()
{
	if (IsRunningLM)
	{
		IsRunningLM = false;
		GetWorldTimerManager().ClearTimer(LMFireTHandle);
	}
}
void ABasePlayerCharacter::CombatLMDelay()
{
	CanLM = true;
}
void ABasePlayerCharacter::CombatLMFire()
{
	//*기능 실현부
	BaseHitscan->Fire();

	//*후행 조건 설정부
	IsJog = false;
	HandleCombatState();
	CanLM = false;
	GetWorldTimerManager().SetTimer(LMFireDelayTHandle, this, &ABasePlayerCharacter::CombatLMDelay, FireRate, false);
	ShootPlay = true;
	GetWorldTimerManager().SetTimerForNextTick(this, &ABasePlayerCharacter::SetShootPlayFalse);
	if (DebugOnOff)
	{
		BaseHitscan->DebugLineTrace();
	}
}
void ABasePlayerCharacter::SetShootPlayFalse()
{
	ShootPlay = false;
}

// (skill RM)
void ABasePlayerCharacter::CombatRM()
{
}
void ABasePlayerCharacter::ReSetRuntimeRM()
{
}
void ABasePlayerCharacter::ResetCooldownRM()
{
}
void ABasePlayerCharacter::Aiming()
{
	if (CanRM && !IsDash && !IsRunningE) //*선행 조건 설정부
	{
		//*기능 실현부
		SetThisSpeed(400);
		MyTargetArmLength = 100.0f;
		MyTargetArmLocation = FVector(0, 50, 80);
		MyCameraLocation = FVector(0, 0, 0);

		//*후행 조건 설정부
		IsJog = false;
		IsRunningRM = true;
		ZoomInterpTime = 10;
		CanZoom = true;
	}
}
void ABasePlayerCharacter::UnAiming()
{
	if (IsRunningRM)
	{
		//*기능 실현부
		SetThisSpeed(600);
		MyTargetArmLength = 400.0f;
		MyTargetArmLocation = FVector(0, 0, 55);
		MyCameraLocation = FVector(0, 0, 55);

		//*후행 조건 설정부
		IsRunningRM = false;
		ZoomInterpTime = 10;
		CanZoom = true;
	}
}

// (skill Q)
void ABasePlayerCharacter::CombatQ()
{
	if (CanQ && !InCooldownQ)
	{
		//*선행 조건 설정부
		IsRunningQ = true;
		InCooldownQ = true;
		HandleCombatState();
		IsJog = false;

		const FRotator RotationA = Controller->GetControlRotation();
		const FRotator YawRotation(0, RotationA.Yaw, 0);

		//*기능 실현부

		// 라인트레이스로 경로설정
		FVector LineTraceLocation;
		FRotator LineTraceRotation;
		Controller->GetPlayerViewPoint(LineTraceLocation, LineTraceRotation);
		FVector End = LineTraceLocation + LineTraceRotation.Vector() * 10000;
		FHitResult HitResult;

		bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceLocation, End, ECollisionChannel::ECC_GameTraceChannel1);
		FVector Location = GetMesh()->GetSocketLocation("canon_socket");
		FVector ThisZeroVector;
		ThisZeroVector = HasHit ? HitResult.Location - Location : End - Location;
		FRotator Rotation = ThisZeroVector.Rotation();

		// projectile spawn
		ProjectileMissile = GetWorld()->SpawnActor<AProjectileMissile>(ProjectileMissileClass, Location, Rotation);
		ProjectileMissile->SetOwner(this);

		// Play Muzzle effect
		FVector MuzzleLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		if (ProjectileMuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ProjectileMuzzleEffect, MuzzleLocation, GetActorRotation() + FRotator(0, 90, 0));
		}

		//*후행 조건 설정부
		GetWorldTimerManager().SetTimer(QRuntimeTHandle, this, &ABasePlayerCharacter::ReSetRuntimeQ, RuntimeQ, false);
		GetWorldTimerManager().SetTimer(QCooldownTHandle, this, &ABasePlayerCharacter::ResetCooldownQ, CooldownTimeQ, false);
	}
}
void ABasePlayerCharacter::ReSetRuntimeQ()
{
	IsRunningQ = false;

	CanJog = true;

	CanDash = true;
	CanRM = true;
	CanE = true;
	CanR = true;
}
void ABasePlayerCharacter::ResetCooldownQ()
{
	InCooldownQ = false;
}
float ABasePlayerCharacter::GetCooldownQPercent() const
{
	if (GetWorldTimerManager().GetTimerElapsed(QCooldownTHandle) != -1)
	{
		return GetWorldTimerManager().GetTimerElapsed(QCooldownTHandle) / CooldownTimeQ;
	}
	else
	{
		return 0;
	}
}

// (skill E)
void ABasePlayerCharacter::CombatE()
{
	if (CanE && !InCooldownE)
	{
		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
		if (!IsRunningE) //*선행 조건 설정부
		{
			HandleCombatState();

			//*기능 실현부
			// 마우스 화면 중앙위치 //TODO 필요에 따라 마우스 위치변경 //TODO 마우스 우클릭으로도 fire 가능하게
			int32 ScreenWidth;
			int32 ScreenHeight;
			PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
			PlayerController->SetMouseLocation(ScreenWidth * 0.5f, ScreenHeight * 0.5f);

			// 화면와이드아웃
			MyTargetArmLength = 600;
			MyTargetArmLocation = FVector(0, 0, 100);
			MyCameraLocation = FVector(0, 0, 100);

			// 컨트롤러 rotation 조정
			// FRotator ThisRotation = PlayerController->GetControlRotation();
			// PlayerController->SetControlRotation(FRotator(0, ThisRotation.Yaw, ThisRotation.Roll));

			//*후행 조건 설정부
			IsRunningE = true;
			CanZoom = true;
			CanCameraControl = false;
			DrawERange = true;
		}
		else if (IsRunningE) //*선행 조건 설정부
		{
			//*기능 실현부
			FHitResult HitResult = GetUnderCursorLocation();
			AActor *HitActor = HitResult.GetActor();
			if (HitActor != nullptr)
			{
				UGameplayStatics::ApplyRadialDamage(GetWorld(), EDamage, HitResult.Location, 500.f, nullptr, TArray<AActor *>(), this);
				if (PinPointHitEffect)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PinPointHitEffect, HitResult.Location);
				}
			}

			// 화면와이드인
			MyTargetArmLength = 400.0f;
			MyTargetArmLocation = FVector(0, 0, 55);
			MyCameraLocation = FVector(0, 0, 55);

			//*후행 조건 설정부
			CanZoom = true;
			CanCameraControl = true;
			DrawERange = false;

			HandleCombatState();
			CanJog = true;

			IsRunningE = false;
			InCooldownE = true;
			// GetWorldTimerManager().SetTimer(ERuntimeHandle, this, &ABasePlayerCharacter::ReSetRuntimeE, RuntimeE, false);
			GetWorldTimerManager().SetTimer(ECooldownTHandle, this, &ABasePlayerCharacter::ResetCooldownE, CooldownTimeE, false);

			CanDash = true;
			CanRM = true;
			CanLM = true;
			CanQ = true;
			CanR = true;
		}
	}
}
void ABasePlayerCharacter::ReSetRuntimeE()
{
	IsRunningE = false;

	CanJog = true;

	CanDash = true;
	CanLM = true;
	CanRM = true;
	CanQ = true;
	CanR = true;
}
void ABasePlayerCharacter::ResetCooldownE()
{
	InCooldownE = false;
}
FHitResult ABasePlayerCharacter::GetUnderCursorLocation() const
{
	FHitResult HitResult;
	if (PlayerControllerRef)
	{
		PlayerControllerRef->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		return HitResult;
	}
	return HitResult;
}
float ABasePlayerCharacter::GetCooldownEPercent() const
{
	if (GetWorldTimerManager().GetTimerElapsed(ECooldownTHandle) != -1)
	{
		return GetWorldTimerManager().GetTimerElapsed(ECooldownTHandle) / CooldownTimeE;
	}
	else
	{
		return 0;
	}
}

// (skill R)
void ABasePlayerCharacter::CombatR()
{
	if (CanR && !InCooldownR)
	{
		//*선행 조건 설정부
		IsRunningR = true;
		InCooldownR = true;
		IsJog = false;
		HandleCombatState();

		//*기능 실현부
		FVector Location = GetMesh()->GetSocketLocation("Granade_socket");
		const FRotator Rotation = Controller->GetControlRotation();
		FRotator SpawnPitch = FRotator(0, 0, 0);
		if (60 <= Rotation.Pitch && Rotation.Pitch <= 90)
		{
			SpawnPitch.Pitch = 75;
		}
		else
		{
			SpawnPitch.Pitch = Rotation.Pitch + 15;
		}
		// projectile spawn
		ProjectileGranade = GetWorld()->SpawnActor<AProjectileGranade>(ProjectileGranadeClass, Location, FRotator(SpawnPitch.Pitch, Rotation.Yaw, 0));
		ProjectileGranade->SetOwner(this);

		if (GranadeMuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GranadeMuzzleEffect, Location, GetActorRotation() + FRotator(0, 180, 0));
		}

		//*후행 조건 설정부
		GetWorldTimerManager().SetTimer(RRuntimeTHandle, this, &ABasePlayerCharacter::ReSetRuntimeR, RuntimeR, false);
		GetWorldTimerManager().SetTimer(RCooldownTHandle, this, &ABasePlayerCharacter::ResetCooldownR, CooldownTimeR, false);
	}
}
void ABasePlayerCharacter::ReSetRuntimeR()
{
	IsRunningR = false;

	CanJog = true;

	CanDash = true;
	CanRM = true;
	CanQ = true;
	CanE = true;
}
void ABasePlayerCharacter::ResetCooldownR()
{
	InCooldownR = false;
}
float ABasePlayerCharacter::GetCooldownRPercent() const
{
	if (GetWorldTimerManager().GetTimerElapsed(RCooldownTHandle) != -1)
	{
		return GetWorldTimerManager().GetTimerElapsed(RCooldownTHandle) / CooldownTimeR;
	}
	else
	{
		return 0;
	}
}