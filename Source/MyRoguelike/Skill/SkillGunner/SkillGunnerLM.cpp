// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerLM.h"
#include "../SkillActor/ProjectileGranade.h"
#include "../../MyRoguelike.h"
#include "../../Character/MyRoguelikeCharacter.h"


USkillGunnerLM::USkillGunnerLM() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.
}

void USkillGunnerLM::BeginPlay()
{
	Super::BeginPlay();
}

void USkillGunnerLM::SkillTriggered()
{
	Super::SkillTriggered();
	
}
