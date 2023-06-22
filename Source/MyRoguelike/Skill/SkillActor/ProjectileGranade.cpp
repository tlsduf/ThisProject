// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileGranade.h"

#include <Components/CapsuleComponent.h>


AProjectileGranade::AProjectileGranade()
{
}

void AProjectileGranade::BeginPlay()
{
	Super::BeginPlay();

	//CapsuleComponent->OnComponentHit.AddDynamic(this, &AProjectileGranade::OnHit);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileGranade::BeginOverlapEvent);
}

void AProjectileGranade::_OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
{
	Super::_OnHit(HitComp, HitActor, OtherComp, NormalImpulse, HitResult);
}

void AProjectileGranade::_BeginOverlapEvent(class UPrimitiveComponent* InHitComp, class AActor* InOtherActor, class UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, bool InbFromSweep, const FHitResult & InSweepResult)
{
	Super::_BeginOverlapEvent(InHitComp, InOtherActor, InOtherComp, InOtherBodyIndex, InbFromSweep, InSweepResult);
}