// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerQ.h"
#include "../SkillActor/ProjectileMissile.h"
#include "../../MyRoguelike.h"
#include "../../Character/MyRoguelikeCharacter.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>
#include <Components/SkeletalMeshComponent.h>

USkillGunnerQ::USkillGunnerQ() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.
}

void USkillGunnerQ::BeginPlay()
{
	Super::BeginPlay();
}

void USkillGunnerQ::SkillTriggered()
{
	Super::SkillTriggered();

	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	
	// 라인트레이스로 최종경로설정
	FVector lineTraceLocation;
	FRotator lineTraceRotation;
	GameGetPlayerController()->GetPlayerViewPoint(lineTraceLocation, lineTraceRotation);

	FVector end = lineTraceLocation + lineTraceRotation.Vector() * 10000;
	FHitResult hit;

	bool HasHit = GetWorld()->LineTraceSingleByChannel(hit, lineTraceLocation, end, ECollisionChannel::ECC_GameTraceChannel1);
	FVector shotLocation = ownerPawn->GetMesh()->GetSocketLocation("canon_socket");
	FVector ThisZeroVector = HasHit ? hit.Location - shotLocation : end - shotLocation;
	FRotator shotRotation = ThisZeroVector.Rotation();

	// projectile spawn
	ProjectileMissile = GetWorld()->SpawnActor<AProjectileMissile>(ProjectileMissileClass, shotLocation, shotRotation);
	ProjectileMissile->SetOwner(ownerPawn);
}
