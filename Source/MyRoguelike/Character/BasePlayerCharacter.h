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

private:
//=================================================================================
// 이하 기본 Prop 구성
// bool IsRunningA 는 A의 동작시간 중인가를 판별하는 변수다.
// bool CanA 는 A실행가능여부이다. 기본적으로 IsRunningA가 true일 동안 다른 CanB는 false가 된다. 이 기능은 Tick에서 조건문으로 업데이트한다.
// bool IsCooldownA 는 A가 쿨다운 중인가를 판별하는 변수다.
// float RuntimeA 는 A의 동작시간이다.
// float CooldownTimeA 은 재사용대기시간이다. SetTimer의 인자로 활용한다.
//=================================================================================

	// Movement
	bool IsDash = false;
	bool CanDash = true;
	bool IsCooldownDash = false;

	UPROPERTY(EditAnywhere, Category = "ThisMovement")
	float DashingTime = 0.1f;

	UPROPERTY(EditAnywhere, Category = "ThisMovement")
	float CooldownTimeLShift = 5.f;

	UPROPERTY(EditAnywhere, Category = "ThisMovement")
	float DashDistance = 10000.f;

	UPROPERTY(EditAnywhere, Category = "ThisMovement")
	UParticleSystem* DashEffect;

	void Dash();
	void StopDashing();
	void ResetDash();
	void ResetCooldownDash();
	FTimerHandle DashTHandle;

	// (skill LM)
	UPROPERTY(EditDefaultsOnly, Category = "LM")
	TSubclassOf<ABaseHitscan> BaseHitscanClass;

	UPROPERTY()
	ABaseHitscan *BaseHitscan;

	bool IsRunningLM = false;
	bool CanLM = true;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ShootPlay = false;

	FTimerHandle LMFireDelayTHandle;
	FTimerHandle LMFireTHandle;
	FTimerHandle ShootPlayTHandle;
	void CombatLM();
	void CombatLMReleased();
	void CombatLMDelay();
	void CombatLMFire();
	void SetShootPlayFalse();

	// (skill RM)
	bool IsRunningRM = false;
	bool CanRM = true;

	FTimerHandle RMRuntimeTHandle;
	FTimerHandle RMCooldownTHandle;
	void CombatRM();
	void ReSetRuntimeRM();
	void ResetCooldownRM();

	void Aiming();
	void UnAiming();

	// (skill Q)
	UPROPERTY(EditDefaultsOnly, Category = "skill Q")
	TSubclassOf<AProjectileMissile> ProjectileMissileClass;

	UPROPERTY()
	AProjectileMissile *ProjectileMissile;

	bool IsRunningQ = false;
	bool CanQ = true;
	bool InCooldownQ = false;

	UPROPERTY(EditAnywhere, Category = "skill Q")
	float RuntimeQ = 0.5f;

	UPROPERTY(EditAnywhere, Category = "skill Q")
	float CooldownTimeQ = 5.f;

	UPROPERTY(EditAnywhere, Category = "skill Q")
	UParticleSystem *ProjectileMuzzleEffect;

	FTimerHandle QRuntimeTHandle;
	FTimerHandle QCooldownTHandle;
	void CombatQ();
	void ReSetRuntimeQ();
	void ResetCooldownQ();
	UFUNCTION(BlueprintPure)
	float GetCooldownQPercent() const;

	// (skill E)

	bool IsRunningE = false;
	bool CanE = true;
	bool InCooldownE = false;

	UPROPERTY(EditAnywhere, Category = "skill E")
	float EDamage = 50;

	UPROPERTY(EditAnywhere, Category = "skill E")
	float CooldownTimeE = 5.f;

	APlayerController *PlayerControllerRef;
	bool DrawERange = false;

	UPROPERTY(EditAnywhere, Category = "skill E")
	UParticleSystem *PinPointHitEffect;

	FTimerHandle ERuntimeTHandle;
	FTimerHandle ECooldownTHandle;
	void CombatE();
	void ReSetRuntimeE();
	void ResetCooldownE();
	FHitResult GetUnderCursorLocation() const;
	UFUNCTION(BlueprintPure)
	float GetCooldownEPercent() const;

	// (skill R)
	bool IsRunningR = false;
	bool CanR = true;
	bool InCooldownR = false;

	UPROPERTY(EditAnywhere, Category = "skill R")
	float RuntimeR = 0.3f;

	UPROPERTY(EditAnywhere, Category = "skill R")
	float CooldownTimeR = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "skill R")
	TSubclassOf<AProjectileGranade> ProjectileGranadeClass;

	UPROPERTY()
	AProjectileGranade *ProjectileGranade;

	UPROPERTY(EditAnywhere, Category = "skill R")
	UParticleSystem *GranadeMuzzleEffect;

	FTimerHandle RRuntimeTHandle;
	FTimerHandle RCooldownTHandle;
	void CombatR();
	void ReSetRuntimeR();
	void ResetCooldownR();
	UFUNCTION(BlueprintPure)
	float GetCooldownRPercent() const;
};
