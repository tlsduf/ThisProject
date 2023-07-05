// Fill out your copyright notice in the Description page of Project Settings.

#include "TSUnderCursor.h"
#include "../SkillActor/ProjectileGranade.h"
#include "../../Character/BasePlayerCharacter.h"
#include "../../Character/MyRoguelikeCharacter.h"
#include "../../Logic/RoguelikePlayerController.h"

#include <Kismet/GameplayStatics.h>


UTSUnderCursor::UTSUnderCursor() : Super()
{
	PrimaryComponentTick.bCanEverTick = false; // 일단 Tick은 OFF 해두었습니다.
}

void UTSUnderCursor::BeginPlay()
{
	Super::BeginPlay();
}

void UTSUnderCursor::SkillTriggered()
{
	Super::SkillTriggered();

	auto ownerPawn = Cast<ABasePlayerCharacter>(GetOwner());
	if(ownerPawn == nullptr)
		return;
	APlayerController *ownerController = Cast<ARoguelikePlayerController>(ownerPawn->GetController());
	if(ownerController == nullptr)
		return;
	
	if (!IsE)
	{
		//HandleCombatState();

		//*기능 실현부
		// 마우스 화면 중앙위치 //TODO 필요에 따라 마우스 위치변경 //TODO 마우스 우클릭으로도 fire 가능하게
		int32 ScreenWidth;
		int32 ScreenHeight;
		ownerController->GetViewportSize(ScreenWidth, ScreenHeight);
		ownerController->SetMouseLocation(ScreenWidth * 0.5f, ScreenHeight * 0.5f);

		// 화면와이드아웃
		ownerPawn->MyTargetArmLength = 600;
		ownerPawn->MyTargetArmLocation = FVector(0, 0, 100);
		ownerPawn->MyCameraLocation = FVector(0, 0, 100);

		// 컨트롤러 rotation 조정
		// FRotator ThisRotation = PlayerController->GetControlRotation();
		// PlayerController->SetControlRotation(FRotator(0, ThisRotation.Yaw, ThisRotation.Roll));

		//*후행 조건 설정부
		IsE = true;
		ownerPawn->CanZoom = true;
		ownerPawn->CanCameraControl = false;
		ownerPawn->DrawERange = true;
	}
	else if (IsE) //*선행 조건 설정부
	{
		//*기능 실현부
		FHitResult HitResult = GetUnderCursorLocation();
		AActor *HitActor = HitResult.GetActor();
		if (HitActor != nullptr)
		{
			FActorSpawnParameters param = FActorSpawnParameters();
			param.Owner = GetOwner();
			ProjectileGranade = GetWorld()->SpawnActor<AProjectileGranade>(ProjectileGranadeClass, HitResult.Location, FRotator(0,0, 0), param);
			if (PinPointHitEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PinPointHitEffect, HitResult.Location);
			}
		}

		// 화면와이드인
		ownerPawn->MyTargetArmLength = 400.0f;
		ownerPawn->MyTargetArmLocation = FVector(0, 0, 55);
		ownerPawn->MyCameraLocation = FVector(0, 0, 55);

		//*후행 조건 설정부
		ownerPawn->CanZoom = true;
		ownerPawn->CanCameraControl = true;
		ownerPawn->DrawERange = false;

		//HandleCombatState();
		ownerPawn->CanJog = true;

		IsE = false;
		InCooldownE = true;
		// GetWorldTimerManager().SetTimer(ERuntimeHandle, this, &ABasePlayerCharacter::ReSetRuntimeE, RuntimeE, false);
		//ownerPawn->GetWorldTimerManager().SetTimer(ECooldownHandle, this, &ABasePlayerCharacter::ResetCooldownE, ECooldownTime, false);
	}
}
FHitResult UTSUnderCursor::GetUnderCursorLocation()
{
	FHitResult HitResult;
	auto PlayerControllerRef = GameGetPlayerController();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		return HitResult;
	}
	return HitResult;
}