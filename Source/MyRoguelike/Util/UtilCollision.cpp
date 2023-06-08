// Fill out your copyright notice in the Description page of Project Settings.

#include "UtilCollision.h"
#include "../MyRoguelike.h"


#include <Kismet/GameplayStatics.h>
#include <CollisionShape.h>
#include <DrawDebugHelpers.h>
#include <GameFramework/Character.h>


// =============================================================
// 바닥의 표면 타입을 얻어온다
// =============================================================
void ApplyCapsuleDamage(APawn *OwnerPawn, float Damage, float AttackRadius, float AttackStartPoint, float AttackRange, bool DebugOnOff)
{
	AController *OwnerController = OwnerPawn->GetInstigatorController();
	if (OwnerPawn == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerPawn);

	bool HasHit = GameGetWorld()->SweepSingleByChannel(
		HitResult,
		OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * AttackStartPoint,
		OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * AttackStartPoint + OwnerPawn->GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	AActor *HitActor = HitResult.GetActor();
	if (HasHit)
	{
		if (HitActor != nullptr && HitActor != OwnerPawn)
		{
			UGameplayStatics::ApplyDamage(HitActor, Damage, OwnerController, OwnerPawn, nullptr);
		}
	}

	if (DebugOnOff)
	{
		FVector TraceVec = OwnerPawn->GetActorForwardVector() * AttackRange;
		FVector Center = OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * AttackStartPoint + TraceVec * 0.5f;
		float HalfHeight = AttackRange * 0.5f + AttackRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = (HitActor != nullptr) ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		DrawDebugCapsule(GameGetWorld(),
						 Center,
						 HalfHeight,
						 AttackRadius,
						 CapsuleRot,
						 DrawColor,
						 false,
						 DebugLifeTime);
	}
}