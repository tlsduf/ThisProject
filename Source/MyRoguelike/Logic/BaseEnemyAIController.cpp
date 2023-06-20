// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemyAIController.h"
#include "../Character/MyRoguelikeCharacter.h"

#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Math/Vector.h>

void ABaseEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseEnemyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool ABaseEnemyAIController::IsDead() const
{
    AMyRoguelikeCharacter * ControlledCharacter = Cast<AMyRoguelikeCharacter>(GetPawn());
    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }
    return true;
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        
        GetBlackboardComponent()->SetValueAsVector(TEXT("SpawnLocation"), GetPawn()->GetActorLocation());
    }
    GetWorldTimerManager().SetTimer(SpawnAnimTHandle, this, &ABaseEnemyAIController::SetTruePlaySpawnAnim, SpawnTime, false);
}

bool ABaseEnemyAIController::PlaySpawnAnim()
{
    if(GPlaySpawnAnim)
    {
        return false;
    }
    return true;
}

void ABaseEnemyAIController::SetTruePlaySpawnAnim()
{
    GPlaySpawnAnim = true;
}
