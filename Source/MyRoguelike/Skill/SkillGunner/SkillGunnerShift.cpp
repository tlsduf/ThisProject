// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillGunnerShift.h"
#include "../../Character/MyRoguelikeCharacter.h"
#include "../../Animation/GunnerAnimInstance.h"

#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/SkeletalMeshComponent.h>

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

	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
		return;

	const FVector currentAcceleration = ownerPawn->GetCharacterMovement()->GetCurrentAcceleration();
	float currentAccelLength = currentAcceleration.SizeSquared();
	if (CanDash && currentAccelLength > 0)
	{
		// const FRotator Rotation = Controller->GetControlRotation();	//카메라방향으로 대쉬
		const FRotator rotation = ownerPawn->GetActorRotation();	//이동방향으로 대쉬
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		ownerPawn->GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		ownerPawn->LaunchCharacter(currentAcceleration.GetSafeNormal() * DashDistance, true, true);
		// GetCharacterMovement()->MaxWalkSpeed = DashDistance;	//다른종류의 대쉬(일정시간동안 스피드업)

		//UParticleSystemComponent *ParticleSystemComponent = UGameplayStatics::SpawnEmitterAttached(DashEffect, GetRootComponent());

		//*후행 조건 설정부
		IsDash = true;
		CanDash = false;
		InCooldownDash = true;

		//ownerPawn->SkillGunnerRM->UnAiming();

		ownerPawn->SetZoomOutProp();

		ownerPawn->GetWorldTimerManager().SetTimer(DashTHandle, this, &USkillGunnerShift::StopDashing, DashingTime, false);

		//애니메이션 재생?
		UGunnerAnimInstance* animInst = Cast<UGunnerAnimInstance>(ownerPawn->GetMesh()->GetAnimInstance());
		if (!animInst)
			return;

		animInst->PlayMontage(EAbilityType::Shift, EAroundSkillMontageType::AroundAttack1);
	}
}
void USkillGunnerShift::StopDashing()
{
	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
	{
		return;
	}
	ownerPawn->GetCharacterMovement()->StopMovementImmediately();
	ownerPawn->GetWorldTimerManager().SetTimer(DashTHandle, this, &USkillGunnerShift::ResetDash, 0.2f, false);
	ownerPawn->GetCharacterMovement()->BrakingFrictionFactor = 2.f;
}
void USkillGunnerShift::ResetDash()
{
	auto ownerPawn = Cast<AMyRoguelikeCharacter>(GetOwner());
	if(ownerPawn == nullptr)
	{
		return;
	}
	IsDash = false;
	CanDash = true;
	//SetInCombatFalse();
	ownerPawn->IsJog = true;

	ownerPawn->GetWorldTimerManager().SetTimer(DashTHandle, this, &USkillGunnerShift::ResetCooldownDash, ShiftCooldownTime, false);
}
void USkillGunnerShift::ResetCooldownDash()
{
	InCooldownDash = false;
}