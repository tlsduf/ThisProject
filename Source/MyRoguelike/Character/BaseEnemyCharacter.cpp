// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#include "../Skill/ProjectileGranade.h"
#include "../Skill/BaseMelee.h"

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Melee = GetWorld()->SpawnActor<ABaseMelee>(MeleeClass);
	// BaseMelee->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_r"));
	Melee->SetOwner(this);
}

void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DebugOnOff)
	{
		Melee->DebugCapsule();
	}
}

void ABaseEnemyCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftMouse", IE_Pressed, this, &ABaseEnemyCharacter::MeleeAttackHandle);
	PlayerInputComponent->BindAction("RightMouse", IE_Pressed, this, &ABaseEnemyCharacter::ProjectileAttack);
}

void ABaseEnemyCharacter::MeleeAttackHandle()
{
	if (CanMeleeAttack)
	{
		GetWorldTimerManager().SetTimer(MeleeAttackTHandle, this, &ABaseEnemyCharacter::MeleeAttack, 0.50f, false);
		CanMeleeAttack = false;
		GetWorldTimerManager().SetTimer(CanMeleeAttackTHandle, this, &ABaseEnemyCharacter::SetCanMeleeAttackTrue, 1.10f, false);
		InMeleeAttack = true;
		GetWorldTimerManager().SetTimerForNextTick(this, &ABaseEnemyCharacter::SetInMeleeAttackFalse);
	}
}
void ABaseEnemyCharacter::MeleeAttack()
{
	Melee->AttackCheck();
}

void ABaseEnemyCharacter::SetCanMeleeAttackTrue()
{
	CanMeleeAttack = true;
}
void ABaseEnemyCharacter::SetInMeleeAttackFalse()
{
	InMeleeAttack = false;
}

void ABaseEnemyCharacter::ProjectileAttack()
{
	//*기능 실현부
	FVector Location = GetMesh()->GetSocketLocation("Granade_socket");
	const FRotator Rotation = Controller->GetControlRotation();
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
	ProjectileGranade->SetOwner(this);

	if (GranadeMuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GranadeMuzzleEffect, Location, GetActorRotation() + FRotator(0, 180, 0));
	}
}
