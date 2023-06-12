// Fill out your copyright notice in the Description page of Project Settings.

#include "UtilCollision.h"
#include "../MyRoguelike.h"

#include <CollisionShape.h>
#include <DrawDebugHelpers.h>


// =============================================================
// 전방으로 캡슐스윕을 해 히트된 액터를 받아온다 SweepSingleByChannel
// TODO 싱글말고 멀티로 바꾸면 좋을것 같음
// =============================================================
AActor *UtilCollision::CapsuleSweepForward(APawn *OwnerPawn, float InAttackRadius, float InAttackStartPoint, float InAttackRange, bool InDebugOnOff)
{
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(OwnerPawn);

	bool hasHit = GameGetWorld()->SweepSingleByChannel(
		hit,
		OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * InAttackStartPoint,
		OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * InAttackStartPoint + OwnerPawn->GetActorForwardVector() * InAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(InAttackRadius),
		params);

	AActor *hitActor = hit.GetActor();

	// 디버그 캡슐을 그린다. Red - hit 실패/ Green - hit 성공
	if (InDebugOnOff)
	{
		FVector traceVec = OwnerPawn->GetActorForwardVector() * InAttackRange;
		FVector center = OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * InAttackStartPoint + traceVec * 0.5f;
		float halfHeight = InAttackRange * 0.5f + InAttackRadius;
		FQuat capsuleRot = FRotationMatrix::MakeFromZ(traceVec).ToQuat();
		FColor drawColor = (hitActor != nullptr && hitActor != OwnerPawn) ? FColor::Green : FColor::Red;
		float debugLifeTime = 5.0f;

		DrawDebugCapsule(GameGetWorld(),
						 center,
						 halfHeight,
						 InAttackRadius,
						 capsuleRot,
						 drawColor,
						 false,
						 debugLifeTime);
	}

	return hitActor;
}


// =============================================================
// 전방으로 라인트레이스를 해 히트된 액터를 받아온다 LineTraceSingleByChannel
// =============================================================
AActor *UtilCollision::LineTraceForward(APawn *OwnerPawn, float InAttackRange, bool InDebugOnOff)
{
	AController *OwnerController = OwnerPawn->GetInstigatorController();
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}

	FVector location;
	FRotator rotation;
	OwnerController->GetPlayerViewPoint(location, rotation);
	FVector end = location + rotation.Vector() * InAttackRange;
	
	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(OwnerPawn);

	bool hasHit = GameGetWorld()->LineTraceSingleByChannel(
		hit,
		location,
		end,
		ECollisionChannel::ECC_GameTraceChannel1,
		params);

	AActor *hitActor = hit.GetActor();

	// 디버그 캡슐을 그린다. Red - hit 실패/ Green - hit 성공
	if (InDebugOnOff)
	{
		FVector traceVec = rotation.Vector() * InAttackRange;
		FVector center = location + traceVec * 0.5f;
		float halfHeight = InAttackRange * 0.5f;
		FQuat capsuleRot = FRotationMatrix::MakeFromZ(traceVec).ToQuat();
		FColor drawColor = (hitActor != nullptr && hitActor != OwnerPawn) ? FColor::Green : FColor::Red;
		float debugLifeTime = 5.0f;

		DrawDebugCapsule(GameGetWorld(),
						 center,
						 halfHeight,
						 1,
						 capsuleRot,
						 drawColor,
						 false,
						 debugLifeTime);
	}
	
	return hitActor;
}
