// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ProjectileAttack.h"
#include "../Character/BaseEnemyCharacter.h"

#include <AIController.h>


UBTTask_ProjectileAttack::UBTTask_ProjectileAttack()
{
    NodeName = "ProjectileAttack";
}

EBTNodeResult::Type UBTTask_ProjectileAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
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

    Character->ProjectileAttack();

    return EBTNodeResult::Succeeded;
}
