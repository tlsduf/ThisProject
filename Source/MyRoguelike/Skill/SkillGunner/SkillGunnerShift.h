// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerSkill.h"
#include <CoreMinimal.h>
#include "SkillGunnerShift.generated.h"

/**
 *
 */



UCLASS()
class MYROGUELIKE_API USkillGunnerShift : public UPlayerSkill
{
	GENERATED_BODY()

public:
	// 생성자
	USkillGunnerShift();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SkillTriggered() override;

private:
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

	FTimerHandle DashTHandle;

	void StopDashing();
	void ResetDash();
	void ResetCooldownDash();
	
};
