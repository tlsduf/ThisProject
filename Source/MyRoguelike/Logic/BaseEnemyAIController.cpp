// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemyAIController.h"
#include "../Character/MyRoguelikeCharacter.h"

#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BlackboardComponent.h>


void ABaseEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
    //�� ����� OnPossess�� �ű�. ������ ���Ϳ� ��Ʈ�ѷ� ���ǽ� ũ������ ���� ������ ����...
    /*
    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("SpawnLocation"), GetPawn()->GetActorLocation());

        // SetFocus(PlayerPawn);
        // MoveToActor(PlayerPawn, 200); //200 = radius
        // StopMovement();
    }*/
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

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("SpawnLocation"), GetPawn()->GetActorLocation());
    }
}
