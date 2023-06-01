// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyRoguelike.h"
#include "Modules/ModuleManager.h"

#include <GameFramework/Actor.h>
#include <Kismet/GameplayStatics.h>


IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MyRoguelike, "MyRoguelike" );



// =============================================================
// 월드를 반환한다.
// 
// UObject 기반의 클래스는 단순히 GetWorld() 를 쓰면 됩니다 혹은 GwGetWorld( this );
// C++ 네이티브 클래스에서만 필요한 경우 사용해주세요
// =============================================================
UWorld* GameGetWorld( UObject* InObject )
{
	if ( InObject )
		return InObject->GetWorld();

	FWorldContext* world = GEngine->GetWorldContextFromGameViewport( GEngine->GameViewport );
	if ( !world )
	{
		LOG_SCREEN_COLOR( FColor::Red, TEXT( "Fail Get World!!" ) );
		return nullptr;
	}
	return world->World();
}

// =============================================================
// 내 플레이어 컨트롤러를 반환한다.
// =============================================================
APlayerController* GameGetPlayerController()
{
	for ( FConstPlayerControllerIterator iter = GameGetWorld()->GetPlayerControllerIterator(); iter; ++iter )
	{
		APlayerController* playerController = iter->Get();
		if ( playerController )
			return playerController;
	}

	LOG_SCREEN_COLOR( FColor::Red, TEXT( "Fail Find PlayerController!!" ) );
	return nullptr;
}





DEFINE_LOG_CATEGORY(LogMyRoguelike)
