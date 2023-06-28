// Fill out your copyright notice in the Description page of Project Settings.

#include "UtilCollision.h"
#include "../MyRoguelike.h"

#include <CollisionShape.h>
#include <DrawDebugHelpers.h>
#include <GameFramework/PlayerController.h>


// =============================================================
/**
	 *시작점->끝점까지 구로 스윕 트레이스를 합니다.
	 * @param OutHitResults : Sweep 결과 를 담아주는 배열입니다.
	 * @param InStartLocation : 트레이스의 시작점입니다. (시작 구의 정 가운데)
	 * @param InEndLocation : 트레이스의 끝점 입니다. (끝 구의 정 가운데)
	 * @param InCapsuleRadius : Sweep할 구의 반지름입니다.
	 * @param InDebugOnOff : 디버그캡슐의 Draw를 결정하는 bool변수입니다.
	 */
// =============================================================
bool UtilCollision::CapsuleSweepMulti(TArray<FHitResult>& OutHitResults, const FVector& InStartLocation, const FVector& InEndLocation, const float& InCapsuleRadius, bool InDebugOnOff)
{
	// 디버그 캡슐을 그린다. Red - hit 실패/ Green - hit 성공
	if (InDebugOnOff)
	{
		FVector traceVec = InEndLocation - InStartLocation;
		FVector center = traceVec * 0.5f;
		float halfHeight = traceVec.Size() * 0.5f + InCapsuleRadius;
		FQuat capsuleRot = FRotationMatrix::MakeFromZ(traceVec).ToQuat();
		FColor drawColor = FColor::Red;
		float debugLifeTime = 5.0f;

		DrawDebugCapsule(GameGetWorld(),
						 center,
						 halfHeight,
						 InCapsuleRadius,
						 capsuleRot,
						 drawColor,
						 false,
						 debugLifeTime);
	}
	FCollisionQueryParams params;
	
	return GameGetWorld()->SweepMultiByChannel(
		OutHitResults,
		InStartLocation,
		InEndLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(InCapsuleRadius),
		params);
}


// =============================================================
// 전방으로 라인트레이스를 해 히트정보를 받아온다 LineTraceSingleByChannel
// =============================================================
FHitResult UtilCollision::LineTraceForward(APawn *OwnerPawn, float InAttackRange, bool InDebugOnOff)
{
	AController *OwnerController = OwnerPawn->GetController();
	FHitResult hit;
	if (OwnerPawn == nullptr)
	{
		return hit;
	}

	FVector location;
	FRotator rotation;
	OwnerController->GetPlayerViewPoint(location, rotation);
	FVector end = location + rotation.Vector() * InAttackRange;
	
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
	
	return hit;
}
