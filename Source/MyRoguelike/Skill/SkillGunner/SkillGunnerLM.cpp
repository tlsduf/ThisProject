// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerLM.h"
#include "../SkillActor/ProjectileMissile.h"
#include "../../Character/MyRoguelikeCharacter.h"
#include "../../Animation/GunnerAnimInstance.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>
#include <Components/SkeletalMeshComponent.h>


USkillGunnerLM::USkillGunnerLM() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.
}

void USkillGunnerLM::BeginPlay()
{
	Super::BeginPlay();
}

void USkillGunnerLM::SkillTriggered()
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
	bool Hit = GetWorld()->LineTraceSingleByChannel(hit, lineTraceLocation, end, ECollisionChannel::ECC_GameTraceChannel1);

	// 왼손 오른손 반복
	FVector shotLocationHandL =ownerPawn->GetMesh()->GetSocketLocation("hand_lShotSocket");
	FVector shotLocationHandR =ownerPawn->GetMesh()->GetSocketLocation("hand_rShotSocket");
	ToggleVar = !ToggleVar;	// 호출마다 왼손 오른손 반복토글
	FVector shotLocation = ToggleVar ? shotLocationHandL : shotLocationHandR;
	FRotator shotRotation = (Hit ? hit.Location - shotLocation : end - shotLocation).Rotation();

	//===========================================
	// * MainAction 1 // 반동 애니메이션
	UGunnerAnimInstance* animInst = Cast<UGunnerAnimInstance>(ownerPawn->GetMesh()->GetAnimInstance());
	if (!animInst)
		return;
	
	ToggleVar ? animInst->RotateHandL() : animInst->RotateHandR();

	//===========================================
	// * MainAction 2 // Projectile Spawn
	FActorSpawnParameters param = FActorSpawnParameters();
	param.Owner = GetOwner();
	ProjectileMissile = GetWorld()->SpawnActor<AProjectileMissile>(ProjectileMissileClass, shotLocation, shotRotation, param);
}
