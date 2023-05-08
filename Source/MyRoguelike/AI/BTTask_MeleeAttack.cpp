// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MeleeAttack.h"
#include "AIController.h"

#include "../Character/BaseEnemyCharacter.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
    NodeName = "MeleeAttack";
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    ABaseEnemyCharacter *Character = Cast<ABaseEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->MeleeAttack();

    return EBTNodeResult::Succeeded;
}
