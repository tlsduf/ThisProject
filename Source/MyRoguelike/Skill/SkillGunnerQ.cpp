// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerQ.h"
#include "ProjectileMissile.h"
#include "../MyRoguelike.h"
#include "../Character/MyRoguelikeCharacter.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>

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

	// 라인트레이스로 최종경로설정
	FVector LineTraceLocation;
	FRotator LineTraceRotation;
	GameGetPlayerController()->GetPlayerViewPoint(LineTraceLocation, LineTraceRotation);

	FVector End = LineTraceLocation + LineTraceRotation.Vector() * 10000;
	FHitResult HitResult;

	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceLocation, End, ECollisionChannel::ECC_GameTraceChannel1);
	FVector Location = Cast<AMyRoguelikeCharacter>(GetOwner())->GetMesh()->GetSocketLocation("canon_socket");
	FVector ThisZeroVector = HasHit ? HitResult.Location - Location : End - Location;
	FRotator Rotation = ThisZeroVector.Rotation();

	// projectile spawn
	ProjectileMissile = GetWorld()->SpawnActor<AProjectileMissile>(ProjectileMissileClass, Location, Rotation);
	ProjectileMissile->SetOwner(Cast<AMyRoguelikeCharacter>(GetOwner()));
}
