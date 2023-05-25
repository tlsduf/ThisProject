// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillGunnerQ.h"
#include "SkillBase.h"
#include "../Common/GameLog.h"
#include "../Skill/ProjectileGranade.h"


USkillGunnerQ::USkillGunnerQ() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.

}

void USkillGunnerQ::BeginPlay()
{
	Super::BeginPlay();
}

void USkillGunnerQ::SkillStarted()
{
	//LOG_SCREEN(TEXT("%s, SkillStarted!"), *GetName());
}

void USkillGunnerQ::SkillOngoing()
{
	//LOG_SCREEN(TEXT("%s, SkillOngoing!"), *GetName());
}

void USkillGunnerQ::SkillTriggered()
{
	//LOG_SCREEN(TEXT("%s, SkillTriggered!"), *GetName());
}

void USkillGunnerQ::SkillCompleted()
{
	//LOG_SCREEN(TEXT("%s, SkillCompleted!"), *GetName());

	// 테스트용 코드입니다. 실제 완료과 입력 완료는 다르니 구분해야합니다.
	//SkillCompletedDelegate.Execute(ESkillCompletedType::Success);
}

void USkillGunnerQ::SkillCanceled()
{
	//LOG_SCREEN(TEXT("%s, SkillCanceled!"), *GetName());

	// 테스트용 코드입니다. 실제 캔슬과 입력 캔슬은 다르니 구분해야합니다.
	//SkillCompletedDelegate.Execute(ESkillCompletedType::Canceled);
}

// =============================================================
// 스킬 사용이 취소되면 호출됩니다.
// =============================================================
void USkillGunnerQ::CancelSkill()
{
	Super::CancelSkill();
}