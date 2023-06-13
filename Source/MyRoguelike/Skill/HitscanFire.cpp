// Fill out your copyright notice in the Description page of Project Settings.

#include "HitscanFire.h"
#include "../Util/UtilCollision.h"

#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>

void UHitscanFire::BeginPlay()
{
	Super::BeginPlay();
}

void UHitscanFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHitscanFire::SkillTriggered()
{
	Super::SkillTriggered();

	// 데미지 프레임워크를 위한 Instigator, Causer
	APawn *ownerPawn = Cast<APawn>(GetOwner());
	AController *ownerController = ownerPawn->GetInstigatorController();
	if (ownerPawn == nullptr)
	{
		return;
	}

	// 충돌 검사
	FHitResult hit = UtilCollision::LineTraceForward(ownerPawn, AttackRange, DebugOnOff);
	AActor *hitActor = hit.GetActor();

	// 데미지 정보 전달
	if (hitActor != nullptr && hitActor != ownerPawn)
	{
		UGameplayStatics::ApplyDamage(hitActor, Damage, ownerController, ownerPawn, nullptr);
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, hit.Location);
		}
	}
}
