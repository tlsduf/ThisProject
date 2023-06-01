// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


// =============================================================
// Unreal Engine Header
// =============================================================
#include <CoreMinimal.h>
#include <Engine/World.h>
#include <Engine/Engine.h>
#include <UObject/ObjectMacros.h>
#include <Misc/Build.h>
#include <Templates/SubclassOf.h>
#include <Templates/Function.h>

// =============================================================
// C++ Header
// =============================================================
#include <functional>

// =============================================================
// GuardiansW Header
//		(전역 인클루드가 굳이 필요한지?)
//		Include-What-You-Use (IWYU) 를 지키는지 꼭 확인
//		컴파일 시간에 직접적인 영향을 줍니다
// =============================================================
#include "Common/GameLog.h"



// 월드를 반환한다.
UWorld* GameGetWorld( UObject* InObject = nullptr );

// 내 플레이어 컨트롤러를 반환한다.
APlayerController* GameGetPlayerController();





DECLARE_LOG_CATEGORY_EXTERN(LogMyRoguelike, Log, All);
