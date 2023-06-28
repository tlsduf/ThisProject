// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerSkill.h"
#include <CoreMinimal.h>
#include "SkillGunnerLM.generated.h"

/**
 *
 */
class AProjectileMissile;
class UNiagaraSystem;

UCLASS()
class MYROGUELIKE_API USkillGunnerLM : public UPlayerSkill
{
	GENERATED_BODY()

public:
	// 생성자
	USkillGunnerLM();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SkillTriggered() override;

private:
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UNiagaraSystem *ThisShotParticle;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UParticleSystem *ThisShotParticleParticles;
	
	UPROPERTY(EditDefaultsOnly, Category = "MyCustomCategory")
	TSubclassOf<AProjectileMissile> ProjectileMissileClass;

	UPROPERTY()
	AProjectileMissile *ProjectileMissile;
};
