// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "MonsterAnimInstace.generated.h"

/**
 * 
 */
UCLASS()
class MYROGUELIKE_API UMonsterAnimInstace : public UAnimInstance
{
	GENERATED_BODY()
	
private:

public:
	virtual void NativeUpdateAnimation(float InDeltaSeconds) override;

};
