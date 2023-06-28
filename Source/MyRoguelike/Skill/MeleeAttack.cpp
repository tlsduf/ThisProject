// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeAttack.h"
#include "../Util/UtilCollision.h"

#include <Kismet/GameplayStatics.h>

void UMeleeAttack::BeginPlay()
{
	Super::BeginPlay();
}

void UMeleeAttack::SkillTriggered()
{
	Super::SkillTriggered();

	// 데미지 프레임워크를 위한 Instigator, Causer
	APawn *ownerPawn = Cast<APawn>(GetOwner());
	AController *ownerController = ownerPawn->GetController();
	if (ownerPawn == nullptr)
	{
		return;
	}

	// 충돌 검사
	TArray<FHitResult> sweepResults;
	FVector startLocation = ownerPawn->GetActorLocation() + ownerPawn->GetActorForwardVector() * AttackStartPoint;
	FVector endLocation = startLocation + ownerPawn->GetActorForwardVector() * AttackRange;
	UtilCollision::CapsuleSweepMulti(sweepResults, startLocation, endLocation, AttackRadius, DebugOnOff);

	// 데미지 전달
	if(!sweepResults.IsEmpty())
	{
		AActor *hitActor;
		for (auto It = sweepResults.CreateIterator(); It; It++)
		{
			hitActor = It->GetActor();
			UGameplayStatics::ApplyDamage(hitActor, Damage, ownerController, ownerPawn, nullptr);
		}
	}
}
