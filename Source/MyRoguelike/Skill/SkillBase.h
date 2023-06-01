// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillBase.generated.h"

class UInputTrigger;

UCLASS(Blueprintable)
class MYROGUELIKE_API USkillBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USkillBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// Input 상황에 따른 로직 처리 함수들입니다.
	virtual void SkillStarted();
	virtual void SkillOngoing();
	virtual void SkillTriggered();
	virtual void SkillCompleted();
	virtual void SkillCanceled();

	// 스킬이 어떠한 이유로 인해 캔슬될 때 호출됩니다.
	virtual void CancelSkill(){};
};
