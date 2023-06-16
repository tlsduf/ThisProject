// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeAttack.h"
#include "../Util/UtilCollision.h"

#include <GameFramework/PlayerController.h>
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
	AController *ownerController = ownerPawn->GetInstigatorController();
	if (ownerPawn == nullptr)
	{
		return;
	}

	// 충돌 검사
	TArray<FHitResult> hit = UtilCollision::CapsuleSweepForward(ownerPawn, AttackRadius, AttackStartPoint, AttackRange, DebugOnOff);

	// 데미지 전달
	if(hit.IsEmpty())
	{
		AActor *hitActor;
		for (auto It = hit.CreateIterator(); It; It++)
		{
			hitActor = It->GetActor();
			UGameplayStatics::ApplyDamage(hitActor, Damage, ownerController, ownerPawn, nullptr);
		}
	}
}
