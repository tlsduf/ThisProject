// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerSkill.h"
#include <CoreMinimal.h>
#include "SkillGunnerE.generated.h"

/**
 *
 */


UCLASS()
class MYROGUELIKE_API USkillGunnerE : public UPlayerSkill
{
	GENERATED_BODY()

	FTimerHandle ZoomTHandle;
public:
	// 생성자
	USkillGunnerE();

protected:
	virtual void BeginPlay() override;
	//줌인
	void ZoomIn();
	//줌아웃
	void ZoomOut();
public:
	virtual void SkillTriggered() override;

private:

};
