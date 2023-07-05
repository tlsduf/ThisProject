// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerR.h"
#include "../SkillActor/ProjectileGranade.h"
#include "../../Character/MyRoguelikeCharacter.h"
#include "../../Animation/GunnerAnimInstance.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>
#include <Components/SkeletalMeshComponent.h>


USkillGunnerR::USkillGunnerR() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.
}

void USkillGunnerR::BeginPlay()
{
	Super::BeginPlay();
}

void USkillGunnerR::SkillTriggered()
{
	Super::SkillTriggered();

	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
		return;
	auto ownerController = ownerPawn->GetController();
	if(ownerController == nullptr)
		return;
	
	FVector shotLocation = ownerPawn->GetMesh()->GetSocketLocation("Granade_socket");
	const FRotator shotRotation = ownerController->GetControlRotation();
	FRotator spawnPitch = FRotator(0, 0, 0);
	if (60 <= shotRotation.Pitch && shotRotation.Pitch <= 90)
	{
		spawnPitch.Pitch = 75;
	}
	else
	{
		spawnPitch.Pitch = shotRotation.Pitch + 15;
	}
	// projectile spawn
	FActorSpawnParameters param = FActorSpawnParameters();
	param.Owner = GetOwner();
	ProjectileGranade = GetWorld()->SpawnActor<AProjectileGranade>(ProjectileGranadeClass, shotLocation, FRotator(spawnPitch.Pitch, ownerPawn->GetActorRotation().Yaw, 0), param);


	//애니메이션 재생?
	UGunnerAnimInstance* animInst = Cast<UGunnerAnimInstance>(ownerPawn->GetMesh()->GetAnimInstance());
	if (!animInst)
		return;

	animInst->PlayMontage(EAbilityType::SkillR, EAroundSkillMontageType::AroundAttack1);
}
