// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileMissile.generated.h"

/**
 *
 */
UCLASS()
class MYROGUELIKE_API AProjectileMissile : public AProjectileBase
{
	GENERATED_BODY()

public:
	AProjectileMissile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	virtual void _OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult) override;

	virtual void _BeginOverlapEvent(class UPrimitiveComponent* InHitComp, class AActor* InOtherActor, class UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, bool InbFromSweep, const FHitResult & InSweepResult) override;
};
