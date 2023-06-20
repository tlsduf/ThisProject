// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemyCharacter.h"
#include "../Skill/PlayerSkill.h"

#include <Components/InputComponent.h>

#include <TimerManager.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>
#include <Components/SkeletalMeshComponent.h>


ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	MeleeAttack = CreateDefaultSubobject<UPlayerSkill>(TEXT("MeleeAttack"));
	ProjectileAttack = CreateDefaultSubobject<UPlayerSkill>(TEXT("ProjectileAttack"));
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemyCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftMouse", IE_Pressed, this, &ABaseEnemyCharacter::MeleeAttackHandle);
	PlayerInputComponent->BindAction("RightMouse", IE_Pressed, this, &ABaseEnemyCharacter::DoProjectileAttack);
}

void ABaseEnemyCharacter::MeleeAttackHandle()
{
	if (CanMeleeAttack)
	{
		GetWorldTimerManager().SetTimer(MeleeAttackTHandle, this, &ABaseEnemyCharacter::DoMeleeAttack, 0.50f, false);
		CanMeleeAttack = false;
		GetWorldTimerManager().SetTimer(CanMeleeAttackTHandle, this, &ABaseEnemyCharacter::SetCanMeleeAttackTrue, 1.10f, false);
		InMeleeAttack = true;
		GetWorldTimerManager().SetTimerForNextTick(this, &ABaseEnemyCharacter::SetInMeleeAttackFalse);
	}
}
void ABaseEnemyCharacter::DoMeleeAttack()
{
	MeleeAttack->SkillTriggered();
}

void ABaseEnemyCharacter::SetCanMeleeAttackTrue()
{
	CanMeleeAttack = true;
}
void ABaseEnemyCharacter::SetInMeleeAttackFalse()
{
	InMeleeAttack = false;
}

void ABaseEnemyCharacter::DoProjectileAttack()
{
	ProjectileAttack->SkillTriggered();

	FVector Location = GetMesh()->GetSocketLocation("Granade_socket");
	if (GranadeMuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GranadeMuzzleEffect, Location, GetActorRotation() + FRotator(0, 180, 0));
	}
}
