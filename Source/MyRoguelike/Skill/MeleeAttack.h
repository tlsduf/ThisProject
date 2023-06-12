// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerSkill.h"
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

	// 소유한 액터의 위치와 캡슐이 스윕을 시작하는 위치 사이의 거리
	UPROPERTY(EditAnywhere, Category = Melee)
	float AttackStartPoint = 0.f;

	// 스윕이 시작하는 위치와 스윕이 끝나는 위치 사이의 거리
	UPROPERTY(EditAnywhere, Category = Melee)
	float AttackRange = 50.f;

	// 캡슐의 반지름
	UPROPERTY(EditAnywhere, Category = Melee)
	float AttackRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = Melee)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = Debug)
	bool DebugOnOff = true;

public:
	virtual void SkillTriggered() override;
};
