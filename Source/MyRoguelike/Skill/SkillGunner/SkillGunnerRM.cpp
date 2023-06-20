// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerRM.h"
#include "../../Character/MyRoguelikeCharacter.h"

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

	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
	{
		return;
	}
	
	ownerPawn->SetThisSpeed(400);
	ownerPawn->MyTargetArmLength = 100.0f;
	ownerPawn->MyTargetArmLocation = FVector(0, 50, 80);
	ownerPawn->MyCameraLocation = FVector(0, 0, 0);

	ownerPawn->CanZoom = true;
}
void USkillGunnerRM::SkillCompleted()
{
	Super::SkillCompleted();
	
	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
	{
		return;
	}
	
	ownerPawn->SetThisSpeed(600);
	ownerPawn->MyTargetArmLength = 400.0f;
	ownerPawn->MyTargetArmLocation = FVector(0, 0, 55);
	ownerPawn->MyCameraLocation = FVector(0, 0, 55);

	ownerPawn->CanZoom = true;
}
