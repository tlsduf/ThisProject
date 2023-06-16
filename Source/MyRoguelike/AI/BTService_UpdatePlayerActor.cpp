// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_UpdatePlayerActor.h"
#include "../Logic/BaseEnemyAIController.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Pawn.h>
#include <AIController.h>



UBTService_UpdatePlayerActor::UBTService_UpdatePlayerActor()
{
    NodeName = "Update Player Actor";
}

void UBTService_UpdatePlayerActor::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    APawn *AIPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

    FVector VRange = AIPawn->GetActorLocation() - PlayerPawn->GetActorLocation();
    float FRange = VRange.Size();
    // UE_LOG(LogTemp, Warning, TEXT("%f"), FRange);

    if (FRange > 1500)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("InRange"), false);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("InMeleeRange"), false);
    }
    else if (FRange < 1500 && FRange > 250)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("InRange"), true);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("InMeleeRange"), false);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("InRange"), false);
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("InMeleeRange"), true);
    }

    ABaseEnemyAIController * Controller = Cast<ABaseEnemyAIController>(OwnerComp.GetAIOwner());

    if (Controller->IsDead())
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsLive"), false);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsLive"), true);
    }
}
