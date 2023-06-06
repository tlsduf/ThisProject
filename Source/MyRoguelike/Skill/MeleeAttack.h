// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerSkill.h"
#include <CoreMinimal.h>
#include "MeleeAttack.generated.h"

/**
 *
 */
class AApplyRadialDamage;


UCLASS()
class MYROGUELIKE_API UMeleeAttack : public UPlayerSkill
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AApplyRadialDamage> MeleeClass;

	UPROPERTY()
	AApplyRadialDamage *Melee;

	UPROPERTY(EditAnywhere, Category = Melee)
	float AttackRange = 50.f;

	UPROPERTY(EditAnywhere, Category = Melee)
	float AttackRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = Melee)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = Debug)
	bool DebugOnOff = true;

public:
	virtual void SkillTriggered() override;
};
