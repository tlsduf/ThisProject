// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerSkill.h"
#include <CoreMinimal.h>
#include "SkillGunnerQ.generated.h"

/**
 *
 */
class AProjectileMissile;


UCLASS()
class MYROGUELIKE_API USkillGunnerQ : public UPlayerSkill
{
	GENERATED_BODY()

public:
	// 생성자
	USkillGunnerQ();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SkillTriggered() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "skill")
	TSubclassOf<AProjectileMissile> ProjectileMissileClass;

	UPROPERTY()
	AProjectileMissile *ProjectileMissile;
};
