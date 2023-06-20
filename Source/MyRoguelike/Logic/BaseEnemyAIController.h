// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYROGUELIKE_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree *AIBehavior;

	UPROPERTY(EditAnywhere)
	float SpawnTime = 1.0f;

	FTimerHandle SpawnAnimTHandle;
	
	bool GPlaySpawnAnim = false;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool IsDead() const;
	bool PlaySpawnAnim();
	void SetTruePlaySpawnAnim();
	
};
