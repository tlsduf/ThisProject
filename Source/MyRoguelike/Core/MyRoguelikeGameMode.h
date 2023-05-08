// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyRoguelikeGameMode.generated.h"

UCLASS(minimalapi)
class AMyRoguelikeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyRoguelikeGameMode();

	void PawnKilled(APawn *PawnKilled);

protected:
	virtual void BeginPlay() override;

private:
	void HandleGameStart();

	void EndGame(bool bIsPlayerWinner);
};
