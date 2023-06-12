// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerSkill.h"
#include "HitscanFire.generated.h"

/**
 *
 */
class AHitscanBase;


UCLASS()
class MYROGUELIKE_API UHitscanFire : public UPlayerSkill
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
private:

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float AttackRange = 10000;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = Debug)
	bool DebugOnOff = true;

public:
	virtual void SkillTriggered() override;
};
