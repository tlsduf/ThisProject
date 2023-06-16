// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileMissile.h"

#include <GameFramework/DamageType.h>

AProjectileMissile::AProjectileMissile()
{
}

void AProjectileMissile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileMissile::OnHit);
}

void AProjectileMissile::_OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
{
	Super::_OnHit(HitComp, HitActor, OtherComp, NormalImpulse, HitResult);
}