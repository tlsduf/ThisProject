// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill.h"
#include "../Common/GameLog.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(PlayerSkill)

UPlayerSkill::UPlayerSkill() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPlayerSkill::BeginPlay()
{
	Super::BeginPlay();
}

// =============================================================
// 스킬 사용 시작시 호출됩니다.
// =============================================================
void UPlayerSkill::SkillStarted()
{
	LOG_SCREEN(TEXT("%s, SkillStarted!"), *GetName());
}

// =============================================================
// 스킬이 시작되고 트리거 되기전까지 계속 호출됩니다. (아마도)..
// =============================================================
void UPlayerSkill::SkillOngoing()
{
	LOG_SCREEN(TEXT("%s, SkillOngoing!"), *GetName());
}

// =============================================================
// 스킬 입력이 Triggered일 때 호출됩니다.
// =============================================================
void UPlayerSkill::SkillTriggered()
{
	//LOG_SCREEN(TEXT("%s, SkillTriggered!"), *GetName());
}

// =============================================================
// 스킬 입력이 Triggered 후 입력이 해제되거나, Triggered가 호출 된 후 호출됩니다.
// TriggerType에 따라 다릅니다.
// =============================================================
void UPlayerSkill::SkillCompleted()
{
	LOG_SCREEN(TEXT("%s, SkillCompleted!"), *GetName());
}

// =============================================================
// 스킬 입력이 Ongoing 중 입력이 해제되면 호출됩니다.
// =============================================================
void UPlayerSkill::SkillCanceled()
{
	LOG_SCREEN(TEXT("%s, SkillCanceled!"), *GetName());
}

// =============================================================
// 스킬 사용이 취소되면 호출됩니다.
// =============================================================
void UPlayerSkill::CancelSkill()
{
	Super::CancelSkill();
}
