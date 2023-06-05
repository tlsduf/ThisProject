// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "PlayerSkill.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYROGUELIKE_API UPlayerSkill : public USkillBase
{
	GENERATED_BODY()
	
	public:
	// 생성자
	UPlayerSkill();
	
protected:
	virtual void BeginPlay() override;

private:
	// 해당 스킬이 어떤 입력 방식을 가지는지 설정합니다.
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputTrigger> TriggerType;
	
public:
	// TriggerType Getter입니다.
	FORCEINLINE const TObjectPtr<UInputTrigger>& GetTriggerType() const { return TriggerType; }
	
	// Input 상황에 따른 로직 처리 함수들입니다.
	virtual void SkillStarted() override;
	virtual void SkillOngoing() override;
	virtual void SkillTriggered() override;
	virtual void SkillCompleted() override;
	virtual void SkillCanceled() override;

	// 스킬이 어떠한 이유로 인해 캔슬될 때 호출됩니다.
	virtual void CancelSkill() override;
};
