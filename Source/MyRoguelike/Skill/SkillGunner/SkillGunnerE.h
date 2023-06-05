// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerSkill.h"
#include <CoreMinimal.h>
#include "SkillGunnerE.generated.h"

/**
 *
 */
class AProjectileMissile;


UCLASS()
class MYROGUELIKE_API USkillGunnerE : public UPlayerSkill
{
	GENERATED_BODY()

public:
	// 생성자
	USkillGunnerE();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SkillTriggered() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "MyCustomCategory")
	TSubclassOf<AProjectileMissile> ProjectileMissileClass;

	UPROPERTY()
	AProjectileMissile *ProjectileMissile;
};
