// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyRoguelikeGameMode.h"
#include "../Logic/RoguelikePlayerController.h"

#include <UObject/ConstructorHelpers.h>



AMyRoguelikeGameMode::AMyRoguelikeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMyRoguelikeGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AMyRoguelikeGameMode::PawnKilled(APawn *PawnKilled)
{
	if(PawnKilled->GetController() != GameGetPlayerController())
	{
		LOG_SCREEN(TEXT("EnemyDied"))
		return;
	}
	auto PlayerController = Cast<ARoguelikePlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		LOG_SCREEN(TEXT("Disable Input"))
		PlayerController->SetPlayerEnabledState(false);
		EndGame(false);
	}

 	/*for (ABaseEnemyAIController *Controller : TActorRange<ABaseEnemyAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}
	} 

	EndGame(true);*/
	
}

void AMyRoguelikeGameMode::HandleGameStart()
{
}

void AMyRoguelikeGameMode::EndGame(bool bIsPlayerWinner)
{
	LOG_SCREEN(TEXT("YouDied"));
}