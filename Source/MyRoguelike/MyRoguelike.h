// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


// =============================================================
// Unreal Engine Header
// =============================================================
#include <CoreMinimal.h>
#include <TimerManager.h>
#include <Engine/World.h>
#include <Engine/Engine.h>
#include <Engine/GameInstance.h>
#include <UObject/ObjectMacros.h>
#include <Misc/Build.h>
#include <Templates/SubclassOf.h>
#include <Templates/Function.h>
#include <ProfilingDebugging/ScopedTimers.h>


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
#include "Common/Enum.h"



// 월드를 반환한다.
UWorld* GameGetWorld( UObject* InObject = nullptr );

// 현재 월드가 프리뷰 월드 ( 블루 프린트 월드 ) 인지 반환한다.
bool GameIsPreviewWorld( UWorld* InWorld );

// 게임 인스턴스를 반환한다.
UGameInstance* GameGetGameInstance( UWorld* InWorld = nullptr );

// 내 플레이어 컨트롤러를 반환한다.
APlayerController* GameGetPlayerController();


DECLARE_LOG_CATEGORY_EXTERN(LogMyRoguelike, Log, All);

// =============================================================
// 게임 인스턴스를 반환한다.
// UGameInstance 기반 클래스로 캐스팅해서 반환
// =============================================================
template<typename Type>
Type* GameGetGameInstance( UWorld* InWorld = nullptr )
{
	return Cast< Type >(GameGetGameInstance( InWorld ));
}

// =============================================================
// 내 플레이어 컨트롤러를 반환한다.
// APlayerController 기반 클래스로 캐스팅해서 반환
// =============================================================
template<typename Type>
Type* GameGetPlayerController()
{
	return Cast< Type >(GameGetPlayerController( InWorld ));
}