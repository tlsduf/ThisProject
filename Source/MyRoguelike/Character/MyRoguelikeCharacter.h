// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyRoguelikeCharacter.generated.h"

class UPlayerSkill;

class ABaseHitscan;

class ABaseProjectile;
class AProjectileGranade;
class AProjectileMissile;

class ABaseMelee;

UCLASS(config = Game)
class AMyRoguelikeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *FollowCamera;

	// 스킬을 할당받기 위한 배열입니다. (BP에서도 받을 수 있도록 TSubClassOf로 하였습니다)
	UPROPERTY(EditAnywhere, Category = Skill)
	TArray<TSubclassOf<UPlayerSkill>> SkillInfos;

	// 런타임에 인스턴스화된 스킬들을 담는 배열입니다. (실제로 이 배열에 담긴 스킬들을 호출)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = Skill, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UPlayerSkill>> Skills;

public:
	AMyRoguelikeCharacter();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// 런타임에 스킬들을 인스턴스화 시킵니다. PlayerController에서 Pose시 호출합니다.
	void InitSkills();

	// 런타임에 인스턴스화 된 Skills Getter입니다.
	FORCEINLINE const TArray<TObjectPtr<UPlayerSkill>> &GetSkills() const { return Skills; }

	// PlayerController에서 호출될 스킬 발동 함수들입니다.
	virtual void SkillStarted(const uint8 &InSkillIndex);
	virtual void SkillOngoing(const uint8 &InSkillIndex);
	virtual void SkillTriggered(const uint8 &InSkillIndex);
	virtual void SkillCompleted(const uint8 &InSkillIndex);
	virtual void SkillCanceled(const uint8 &InSkillIndex);

public:
	/** Called for movement input */
	void Move(const FInputActionValue &Value);

	/** Called for looking input */
	void Look(const FInputActionValue &Value);

	// !MyCode------------------------------------------------------
protected:
	// Debug
	void DebugActorRotation();

public:
	// Zoom
	void SetZoomInProp();
	void SetZoomOutProp();
	void ZoomInOut(float DeltaTime);

	void Jog();
	void WPressed();
	void WReleased();

protected:
	// RotatePawn
	void RotatePawn(float DeltaTime);

	// Movement
	void SetThisSpeed(float Speed);
	void SetThisJogSpeed(float JogSpeed);
	void CalculateSpeed();

	// TakeDamageHandle
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;
	void SetTakeDamageAnimFalse();
	void SetCanTakeDamageAnimTrue();
	FTimerHandle TakeDamageAnimHandle;

	// CombatState
	void HandleCombatState();
	void SetInCombatFalse();

public:
	bool GetCombatState();
	// !------------------------------------------------------------

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent *GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent *GetFollowCamera() const { return FollowCamera; }

	// !MyCode------------------------------------------------------
public:
	// * 임시 죽는애니메이션 play
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// * 체력바UI
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// * 데미지UI
	UFUNCTION(BlueprintPure)
	float GetDamage() const;

	float DamageText;

protected:
	// * 디버그on/off
	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool DebugOnOff = 0;

	// * 줌인아웃 & 카메라조종가능
	bool IsZoomed = false;
	bool CanZoom = true;
	float ZoomInterpTime = 6;

	UPROPERTY()
	float MyTargetArmLength = 400.0f;

	UPROPERTY()
	FVector MyTargetArmLocation = FVector(0, 0, 45);

	UPROPERTY()
	FVector MyCameraLocation = FVector(0, 0, 70);

	bool CanCameraControl = true;

	// * Pawn Rotate
	bool IsRotate = false;
	bool CanRotate = false;

	// * 전투state
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool InCombat = false;

	FTimerHandle CombatStateTHandle;

	// * 초기속력(default), 현재속력(this) 로 구분.
	// TODO ThisSpeed = DefaultSpeed + DefaultSpeed * 아이템효과
	UPROPERTY(EditAnywhere, Category = "BaseMovement")
	float DefaultSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "BaseMovement")
	float ThisSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "BaseMovement")
	float DefaultJogSpeed = 1200.f;

	UPROPERTY(EditAnywhere, Category = "BaseMovement")
	float ThisJogSpeed = 800.f;

	// * w눌린상태>달리기가능   달리는상태>w때기>달리기종료
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsJog = false;

	bool CanJog = true;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsWPressed = false;

	// * 연속점프횟수 bp에서 간접적으로 건드리기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseMovement", meta = (AllowPrivateAccess = "true"))
	int32 ThisJumpMaxCount = 1;

	// * 체력 및 방어력 및 특수
	// TODO 방어력 기능 구현
	UPROPERTY(EditDefaultsOnly, Category = "Defensive")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Defensive")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Defensive")
	int Armor = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Defensive")
	bool DamageImmunity = false; // true > 무적
	// TODO 각종 공격효과 무효 bool

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool TakeDamageAnim = false;

	bool CanTakeDamageAnim = true;
	FTimerHandle TakeDamageHandle;

	// * 공격관련 변수
	UPROPERTY(EditAnywhere, Category = "CombatProp")
	float FireRate = 0.25f;

protected:
	// * 키bool Anim블루프린트 몽타주 실행용 // 블루프린트에서만 사용하고있다.
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsQPressed = false;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsEPressed = false;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsRPressed = false;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsZPressed = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsLMPressed = false;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsRMPressed = false;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsLShiftPressed = false;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsSpacePressed = false;

	// !------------------------------------------------------------
};
