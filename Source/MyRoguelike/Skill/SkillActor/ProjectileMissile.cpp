// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileMissile.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/DamageType.h>

AProjectileMissile::AProjectileMissile()
{
	
}

void AProjectileMissile::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentHit.AddDynamic(this, &AProjectileMissile::OnHit);
	//CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileMissile::OnHit);
	//CapsuleComponent->OnComponentHit.AddDynamic(this, &AProjectileMissile::BeginPlay);
}

void AProjectileMissile::_OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
{
	Super::_OnHit(HitComp, HitActor, OtherComp, NormalImpulse, HitResult);
}