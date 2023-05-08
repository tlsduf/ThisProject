// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyRoguelikeCharacter.h"
#include "BasePlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class MYROGUELIKE_API ABasePlayerCharacter : public AMyRoguelikeCharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// !MyCode------------------------------------------------------
	// Movement
	void Dash();
	void StopDashing();
	void ResetDash();
	void ResetCooldownDash();
	FTimerHandle DashHandle;

	// Combat 

	// (skill LM)
	void CombatLM();
	void CombatLMReleased();
	void CombatLMDelay();
	void CombatLMFire();
	void SetShootPlayFalse();
	FTimerHandle LMFireDelayHandle;
	FTimerHandle LMFireHandle;
	FTimerHandle ShootPlayHandle;

	// (skill RM)
	void CombatRM();
	void ReSetRuntimeRM();
	void ResetCooldownRM();
	FTimerHandle RMRuntimeHandle;
	FTimerHandle RMCooldownHandle;
	void Aiming();
	void UnAiming();

	// (skill Q)
	void CombatQ();
	void ReSetRuntimeQ();
	void ResetCooldownQ();
	FTimerHandle QRuntimeHandle;
	FTimerHandle QCooldownHandle;
	UFUNCTION(BlueprintPure)
	float GetCooldownQPercent() const;

	// (skill E)
	void CombatE();
	void ReSetRuntimeE();
	void ResetCooldownE();
	FTimerHandle eRuntimeHandle;
	FTimerHandle ECooldownHandle;
	FHitResult GetUnderCursorLocation() const;
	UFUNCTION(BlueprintPure)
	float GetCooldownEPercent() const;

	// (skill R)
	void CombatR();
	void ReSetRuntimeR();
	void ResetCooldownR();
	FTimerHandle RRuntimeHandle;
	FTimerHandle RCooldownHandle;
	UFUNCTION(BlueprintPure)
	float GetCooldownRPercent() const;
	// !------------------------------------------------------------

private:
	/*
	* 이하 기본 Prop 구성
	bool IsA 는 A의 동작시간 중인가를 판별하는 변수다.
	float RuntimeA 는 A의 동작시간이다.	SetTimer의 인자로 활용한다.	RuntimeA는 공격속도or스킬시전속도에 관여하는 변수에 영향을 받게 함수를 짤 것.
	bool CanA 는 A실행가능여부이다.		기본적으로 IsA가 true일 동안 다른 CanB는 false가 된다. 이 기능은 Tick에서 조건문으로 업데이트한다.
	bool InCooldownA 는 A가 쿨다운 중인가를 판별하는 변수다.
	loat ACooldownTime 은 재사용대기시간이다. SetTimer의 인자로 활용한다.
	*/

	// *대쉬
	bool IsDash = false;
	UPROPERTY(EditAnywhere, Category = "ThisMovement")
	float DashingTime = 0.1f;
	bool CanDash = true;
	bool InCooldownDash = false;
	UPROPERTY(EditAnywhere, Category = "ThisMovement")
	float ShiftCooldownTime = 5.f;

	UPROPERTY(EditAnywhere, Category = "ThisMovement")
	float DashDistance = 10000.f;

	UPROPERTY(EditAnywhere, Category = "ThisMovement")
	UParticleSystem *DashEffect;

	// * 공격 (skill LM)
	bool IsLM = false;
	bool CanLM = true;

	UPROPERTY(EditDefaultsOnly, Category = "LM")
	TSubclassOf<ABaseHitscan> BaseHitscanClass;
	UPROPERTY()
	ABaseHitscan *BaseHitscan;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ShootPlay = false;

	// * (skill RM) Aim
	bool IsRM = false;
	//UPROPERTY(EditAnywhere, Category = "skill RM")
	//float RuntimeRM = 0.3f;
	bool CanRM = true;
	//bool InCooldownRM = false;
	//UPROPERTY(EditAnywhere, Category = "skill RM")
	//float RMCooldownTime = 5.f;

	// * (skill Q) Projectile
	bool IsQ = false;
	UPROPERTY(EditAnywhere, Category = "skill Q")
	float RuntimeQ = 0.5f;
	bool CanQ = true;
	bool InCooldownQ = false;
	UPROPERTY(EditAnywhere, Category = "skill Q")
	float QCooldownTime = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "skill Q")
	TSubclassOf<AProjectileMissile> ProjectileMissileClass;
	UPROPERTY()
	AProjectileMissile *ProjectileMissile;

	UPROPERTY(EditAnywhere, Category = "skill Q")
	UParticleSystem *ProjectileMuzzleEffect;

	// * (skill E) PinPoint
	UPROPERTY(EditAnywhere, Category = "skill E")
	float EDamage = 50;
	bool IsE = false;
	bool CanE = true;
	bool InCooldownE = false;
	UPROPERTY(EditAnywhere, Category = "skill E")
	float ECooldownTime = 5.f;

	APlayerController *PlayerControllerRef;
	bool DrawERange = false;

	UPROPERTY(EditAnywhere, Category = "skill E")
	UParticleSystem *PinPointHitEffect;

	// * (skill R) Projectile Granade
	bool IsR = false;
	UPROPERTY(EditAnywhere, Category = "skill R")
	float RuntimeR = 0.3f;
	bool CanR = true;
	bool InCooldownR = false;
	UPROPERTY(EditAnywhere, Category = "skill R")
	float RCooldownTime = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "skill R")
	TSubclassOf<AProjectileGranade> ProjectileGranadeClass;
	UPROPERTY()
	AProjectileGranade *ProjectileGranade;

	UPROPERTY(EditAnywhere, Category = "skill R")
	UParticleSystem *GranadeMuzzleEffect;
};
