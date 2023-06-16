// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ProjectileGranade.generated.h"

/**
 *
 */
UCLASS()
class MYROGUELIKE_API AProjectileGranade : public AProjectileBase
{
	GENERATED_BODY()

public:
	AProjectileGranade();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual void _OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult) override;
	
};
