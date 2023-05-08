// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyRoguelikeGameMode.h"


#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

#include "../Logic/BaseEnemyAIController.h"
#include "../Logic/RoguelikePlayerController.h"
#include "../Character/MyRoguelikeCharacter.h"

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
	UE_LOG(LogTemp, Warning, TEXT("PawnKilled Act"));
	APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for (ABaseEnemyAIController *Controller : TActorRange<ABaseEnemyAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}
	}

	EndGame(true);
	
}

void AMyRoguelikeGameMode::HandleGameStart()
{
}

void AMyRoguelikeGameMode::EndGame(bool bIsPlayerWinner)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), bIsPlayerWinner);
}