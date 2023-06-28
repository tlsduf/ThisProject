// Copyright GuardiansW. All Rights Reserved.
//
// 충돌 관련 편의 함수 모음

#pragma once

class UWorld;

namespace UtilCollision
{
	// 전방으로 캡슐스윕을 해 히트정보를 받아온다
	bool CapsuleSweepMulti(TArray<FHitResult>& OutHitResults, const FVector& InStartLocation, const FVector& InEndLocation, const float& InCapsuleRadius, bool InDebugOnOff);

	// 전방으로 라인트레이스를 해 히트정보를 받아온다
	FHitResult LineTraceForward(APawn *OwnerPawn, float InAttackRange, bool InDebugOnOff);
}