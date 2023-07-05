// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerE.h"
#include "../../Character/MyRoguelikeCharacter.h"
#include "../../Animation/GunnerAnimInstance.h"

#include <GameFramework/PlayerController.h>
#include <Components/SkeletalMeshComponent.h>


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

	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
		return;
	auto ownerController = ownerPawn->GetController();
	if(ownerController == nullptr)
		return;

	//데미지 적용
	
	
	//이펙트 소환
	
	
	//애니메이션 재생?
	UGunnerAnimInstance* animInst = Cast<UGunnerAnimInstance>(ownerPawn->GetMesh()->GetAnimInstance());
	if (!animInst)
		return;

	animInst->PlayMontage(EAbilityType::SkillE, EAroundSkillMontageType::AroundAttack1);
	ZoomOut();
	GetWorld()->GetTimerManager().SetTimer(ZoomTHandle, this, &USkillGunnerE::ZoomIn, 2.7f, false);
}

void USkillGunnerE::ZoomIn()
{
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

void USkillGunnerE::ZoomOut()
{
	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
	{
		return;
	}
	
	ownerPawn->SetThisSpeed(600);
	ownerPawn->MyTargetArmLength = 600;
	ownerPawn->MyTargetArmLocation = FVector(-100, 0, 100);
	ownerPawn->MyCameraLocation = FVector(0, 0, 100);

	ownerPawn->CanZoom = true;
}