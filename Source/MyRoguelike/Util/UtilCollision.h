// Copyright GuardiansW. All Rights Reserved.
//
// 충돌 관련 편의 함수 모음

#pragma once

class UWorld;

namespace UtilCollision
{
	// 전방으로 캡슐스윕을 해 히트된 액터를 받아온다
	AActor* CapsuleSweepForward(APawn *OwnerPawn, float InAttackRadius, float InAttackStartPoint, float InAttackRange, bool InDebugOnOff);

	// 전방으로 라인트레이스를 해 히트된 액터를 받아온다
	AActor* LineTraceForward(APawn *OwnerPawn, float InAttackRange, bool InDebugOnOff);
}