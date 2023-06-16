// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerRM.h"
#include "../../Character/MyRoguelikeCharacter.h"

#include <GameFramework/PlayerController.h>

USkillGunnerRM::USkillGunnerRM() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.
}

void USkillGunnerRM::BeginPlay()
{
	Super::BeginPlay();
}

void USkillGunnerRM::SkillStarted()
{
	Super::SkillStarted();

	auto Char = Cast<AMyRoguelikeCharacter>(GetOwner());
	
	Char->SetThisSpeed(400);
	Char->MyTargetArmLength = 100.0f;
	Char->MyTargetArmLocation = FVector(0, 50, 80);
	Char->MyCameraLocation = FVector(0, 0, 0);

	Char->CanZoom = true;
}
void USkillGunnerRM::SkillCompleted()
{
	Super::SkillCompleted();
	
	auto Char = Cast<AMyRoguelikeCharacter>(GetOwner());
	
	Char->SetThisSpeed(600);
	Char->MyTargetArmLength = 400.0f;
	Char->MyTargetArmLocation = FVector(0, 0, 55);
	Char->MyCameraLocation = FVector(0, 0, 55);

	Char->CanZoom = true;
}
