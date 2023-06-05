// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyRoguelikeCharacter.h"
#include "BaseEnemyCharacter.generated.h"

/**
 *
 */

class AProjectileGranade;
class AApplyRadialDamage;

UCLASS()
class MYROGUELIKE_API ABaseEnemyCharacter : public AMyRoguelikeCharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "MyCustomCategory")
	TSubclassOf<AApplyRadialDamage> MeleeClass;
	UPROPERTY()
	AApplyRadialDamage *Melee;

	UPROPERTY(EditDefaultsOnly, Category = "MyCustomCategory")
	TSubclassOf<AProjectileGranade> ProjectileGranadeClass;
	UPROPERTY()
	AProjectileGranade *ProjectileGranade;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UParticleSystem *GranadeMuzzleEffect;

	void MeleeAttackHandle();
	void MeleeAttack();

	void SetCanMeleeAttackTrue();
	void SetInMeleeAttackFalse();
	void ProjectileAttack();

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool InMeleeAttack = false;

	bool CanMeleeAttack = true;
	FTimerHandle MeleeAttackTHandle;
	FTimerHandle CanMeleeAttackTHandle;
};
