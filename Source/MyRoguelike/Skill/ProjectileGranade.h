// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "ProjectileGranade.generated.h"

/**
 *
 */
UCLASS()
class MYROGUELIKE_API AProjectileGranade : public ABaseProjectile
{
	GENERATED_BODY()

public:
	AProjectileGranade();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult);

	UPROPERTY(EditAnywhere)
    float Radius = 500.f;
};
