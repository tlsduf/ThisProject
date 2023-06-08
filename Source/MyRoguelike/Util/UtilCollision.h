// Copyright GuardiansW. All Rights Reserved.
//
// 충돌 관련 편의 함수 모음

#pragma once

class UWorld;


// 데미지 판정을 위한 캡슐스윕
void ApplyCapsuleDamage(APawn *OwnerPawn, float Damage, float AttackRadius, float AttackStartPoint, float AttackRange, bool DebugOnOff);