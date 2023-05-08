// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatePlayerActor.generated.h"

/**
 * 
 */
UCLASS()
class MYROGUELIKE_API UBTService_UpdatePlayerActor : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	

public:
	UBTService_UpdatePlayerActor();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
	
};
