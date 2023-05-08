// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillBase.generated.h"

class UInputTrigger;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 해당 스킬이 어떤 입력 방식을 가지는지 설정합니다.
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputTrigger> TriggerType;
	
public:
	// TriggerType Getter입니다.
	FORCEINLINE const TObjectPtr<UInputTrigger>& GetTriggerType() const { return TriggerType; }
	
	// Input 상황에 따른 로직 처리 함수들입니다.
	virtual void SkillStarted();
	virtual void SkillOngoing();
	virtual void SkillTriggered();
	virtual void SkillCompleted();
	virtual void SkillCanceled();
		
};
