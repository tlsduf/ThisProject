// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerShift.h"
#include "../SkillActor/ProjectileGranade.h"
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

	FVector Location = Cast<AMyRoguelikeCharacter>(GetOwner())->GetMesh()->GetSocketLocation("Granade_socket");
	const FRotator Rotation = GameGetPlayerController()->GetControlRotation();
	FRotator SpawnPitch = FRotator(0, 0, 0);
	if (60 <= Rotation.Pitch && Rotation.Pitch <= 90)
	{
		SpawnPitch.Pitch = 75;
	}
	else
	{
		SpawnPitch.Pitch = Rotation.Pitch + 15;
	}
	// projectile spawn
	ProjectileGranade = GetWorld()->SpawnActor<AProjectileGranade>(ProjectileGranadeClass, Location, FRotator(SpawnPitch.Pitch, Rotation.Yaw, 0));
	ProjectileGranade->SetOwner(Cast<AMyRoguelikeCharacter>(GetOwner()));
}
