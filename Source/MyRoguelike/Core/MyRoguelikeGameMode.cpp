// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyRoguelikeGameMode.h"
#include "../Logic/BaseEnemyAIController.h"
#include "../Logic/RoguelikePlayerController.h"
#include "../Character/MyRoguelikeCharacter.h"


#include <UObject/ConstructorHelpers.h>
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include <GameFramework/Controller.h>



AMyRoguelikeGameMode::AMyRoguelikeGameMode()
{
	static const FName PropertyEditor("PropertyEditor");
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);

#define LOCTEXT_NAMESPACE "PropertySection"
	TSharedRef<FPropertySection> Section1 = PropertyModule.FindOrCreateSection("MyRoguelikeCharacter", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
	Section1->AddCategory("Defensive");
	Section1->AddCategory("Debug");
	Section1->AddCategory("BaseMovement");
	Section1->AddCategory("CombatProp");

	TSharedRef<FPropertySection> Section2 = PropertyModule.FindOrCreateSection("BasePlayerCharacter", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
	Section2->AddCategory("ThisMovement");
	Section2->AddCategory("LM");
	Section2->AddCategory("skill Q");
	Section2->AddCategory("skill E");
	Section2->AddCategory("skill R"); 
#undef LOCTEXT_NAMESPACE

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