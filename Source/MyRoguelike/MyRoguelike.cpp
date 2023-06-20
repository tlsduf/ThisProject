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
// 현재 월드가 프리뷰 월드 ( 블루 프린트 월드 ) 인지 반환한다.
// 
// 사용시 주의사항
// 에디터단에서 테스트를 위한 코드이므로 실제 사용시
// #if WITH_EDITOR
// #if WITH_EDITORONOLY_DATA
// 같은 전처리기를 활용하여 게임 월드 에서는 되도록 호출 자체를 하지 않도록 짜는게 좋습니다
// =============================================================
bool GameIsPreviewWorld( UWorld* InWorld )
{
#if WITH_EDITOR
	if ( InWorld )
		return InWorld->IsPreviewWorld();
#endif

	return false;
}

// =============================================================
// 게임 인스턴스를 반환한다.
// =============================================================
UGameInstance* GameGetGameInstance( UWorld* InWorld )
{
	UWorld* world = InWorld ? InWorld : GameGetWorld();

	return UGameplayStatics::GetGameInstance( world );
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
