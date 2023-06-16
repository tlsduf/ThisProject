// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerShift.h"
#include "../../MyRoguelike.h"
#include "../../Character/MyRoguelikeCharacter.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>

USkillGunnerShift::USkillGunnerShift() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.
}

void USkillGunnerShift::BeginPlay()
{
	Super::BeginPlay();
}

void USkillGunnerShift::SkillTriggered()
{
	Super::SkillTriggered();
	
}
