// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerE.h"
#include "../SkillActor/ProjectileMissile.h"
#include "../../MyRoguelike.h"
#include "../../Character/MyRoguelikeCharacter.h"




USkillGunnerE::USkillGunnerE() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.
}

void USkillGunnerE::BeginPlay()
{
	Super::BeginPlay();
}

void USkillGunnerE::SkillTriggered()
{
	Super::SkillTriggered();
}
