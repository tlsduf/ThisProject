// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerR.h"
#include "../SkillActor/ProjectileGranade.h"
#include "../../MyRoguelike.h"
#include "../../Character/MyRoguelikeCharacter.h"

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
	
	FVector shotLocation = ownerPawn->GetMesh()->GetSocketLocation("Granade_socket");
	const FRotator shotRotation = GameGetPlayerController()->GetControlRotation();
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
	ProjectileGranade = GetWorld()->SpawnActor<AProjectileGranade>(ProjectileGranadeClass, shotLocation, FRotator(spawnPitch.Pitch, Cast<AMyRoguelikeCharacter>(GetOwner())->GetActorRotation().Yaw, 0));
	ProjectileGranade->SetOwner(ownerPawn);
}
