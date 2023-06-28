// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerLM.h"
#include "../SkillActor/ProjectileMissile.h"
#include "../../Character/MyRoguelikeCharacter.h"
#include "../../Util/UtilEffect.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"

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

	if (ThisShotParticle)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached( ThisShotParticle, GetOwner()->GetRootComponent(), "canon_socket", FVector(0,0,0), FRotator(0,0,0), EAttachLocation::KeepRelativeOffset, true );
	}
	if (ThisShotParticleParticles)
	{
		//UGameplayStatics::SpawnEmitterAttached(ThisShotParticleParticles, GetOwner()->GetRootComponent(), "canon_socket", FVector Location, FRotator Rotation, FVector Scale, EAttachLocation::Type LocationType, bool bAutoDestroy, EPSCPoolMethod PoolingMethod, bool bAutoActivateSystem);
	}
	
	// 라인트레이스로 최종경로설정
	FVector lineTraceLocation;
	FRotator lineTraceRotation;
	ownerController->GetPlayerViewPoint(lineTraceLocation, lineTraceRotation);
	
	FVector end = lineTraceLocation + lineTraceRotation.Vector() * 10000;
	FHitResult hit;

	bool HasHit = GetWorld()->LineTraceSingleByChannel(hit, lineTraceLocation, end, ECollisionChannel::ECC_GameTraceChannel1);
	FVector shotLocation = ownerPawn->GetMesh()->GetSocketLocation("canon_socket");
	FVector ThisZeroVector = HasHit ? hit.Location - shotLocation : end - shotLocation;
	FRotator shotRotation = ThisZeroVector.Rotation();

	// projectile spawn
	FActorSpawnParameters param = FActorSpawnParameters();
	param.Owner = GetOwner();
	ProjectileMissile = GetWorld()->SpawnActor<AProjectileMissile>(ProjectileMissileClass, shotLocation, shotRotation, param);
}
