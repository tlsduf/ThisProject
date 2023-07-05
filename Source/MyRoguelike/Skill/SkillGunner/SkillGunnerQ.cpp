// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerQ.h"
#include "../SkillActor/ProjectileMissile.h"
#include "../../Character/MyRoguelikeCharacter.h"
#include "../../Animation/GunnerAnimInstance.h"

#include <GameFramework/PlayerController.h>
#include <Components/SkeletalMeshComponent.h>
#include <TimerManager.h>

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
	if(ownerPawn == nullptr)
		return;
	auto ownerController = ownerPawn->GetController();
	if(ownerController == nullptr)
		return;
	
	
	// 라인트레이스로 최종경로설정
	FVector lineTraceLocation;
	FRotator lineTraceRotation;
	ownerController->GetPlayerViewPoint(lineTraceLocation, lineTraceRotation);
	
	FVector end = lineTraceLocation + lineTraceRotation.Vector() * 10000;
	FHitResult hit;

	bool HasHit = GetWorld()->LineTraceSingleByChannel(hit, lineTraceLocation, end, ECollisionChannel::ECC_GameTraceChannel1);
	FVector shotLocation = ownerPawn->GetMesh()->GetSocketLocation("hand_lShotSocket");
	FVector ThisZeroVector = HasHit ? hit.Location - shotLocation : end - shotLocation;
	FRotator shotRotation = ThisZeroVector.Rotation();

	// projectile spawn
	FActorSpawnParameters param = FActorSpawnParameters();
	param.Owner = GetOwner();
	ProjectileMissile = GetWorld()->SpawnActor<AProjectileMissile>(ProjectileMissileClass, shotLocation, shotRotation, param);


	//애니메이션 재생?
	UGunnerAnimInstance* animInst = Cast<UGunnerAnimInstance>(ownerPawn->GetMesh()->GetAnimInstance());
	if (!animInst)
		return;

	animInst->PlayMontage(EAbilityType::SkillQ, EAroundSkillMontageType::AroundAttack1);

	// 줌인합니다.
	ZoomIn();
	GetWorld()->GetTimerManager().SetTimer(ZoomTHandle, this, &USkillGunnerQ::ZoomOut, 3.0f, false);
}

void USkillGunnerQ::ZoomIn()
{
	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
	{
		return;
	}
	
	ownerPawn->SetThisSpeed(0);
	ownerPawn->MyTargetArmLength = 100.0f;
	ownerPawn->MyTargetArmLocation = FVector(-60, 100, 25);
	ownerPawn->MyCameraLocation = FVector(0, 0, 0);

	ownerPawn->CanZoom = true;
}

void USkillGunnerQ::ZoomOut()
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