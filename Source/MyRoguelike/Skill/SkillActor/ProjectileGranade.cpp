// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileGranade.h"

#include <Components/CapsuleComponent.h>


AProjectileGranade::AProjectileGranade()
{
}

void AProjectileGranade::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentHit.AddDynamic(this, &AProjectileGranade::OnHit);
}

void AProjectileGranade::_OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
{
	Super::_OnHit(HitComp, HitActor, OtherComp, NormalImpulse, HitResult);
}