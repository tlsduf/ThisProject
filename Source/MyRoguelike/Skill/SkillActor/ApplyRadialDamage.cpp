// Fill out your copyright notice in the Description page of Project Settings.

#include "ApplyRadialDamage.h"

#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <CollisionShape.h>
#include <DrawDebugHelpers.h>
#include <GameFramework/Character.h>

// Sets default values
AApplyRadialDamage::AApplyRadialDamage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);

	AttackRadius = 50.0f;
	AttackRange = 200.0f;
}

// Called when the game starts or when spawned
void AApplyRadialDamage::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AApplyRadialDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AApplyRadialDamage::AttackCheck()
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return;
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
		return;

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		OwnerPawn->GetActorLocation(),
		OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	if (HasHit)
	{
		AActor *HitActor = HitResult.GetActor();
		if (HitActor != nullptr)
		{
			UGameplayStatics::ApplyDamage(HitActor, Damage, OwnerController, this, nullptr);
		}
	}

	if (DebugOnOff)
	{
		FVector TraceVec = OwnerPawn->GetActorForwardVector() * AttackRange;
		FVector Center = OwnerPawn->GetActorLocation() + TraceVec * 0.5f;
		float HalfHeight = AttackRange * 0.5f + AttackRadius;
		FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
		FColor DrawColor = HasHit ? FColor::Green : FColor::Red;
		float DebugLifeTime = 5.0f;

		DrawDebugCapsule(GetWorld(),
						 Center,
						 HalfHeight,
						 AttackRadius,
						 CapsuleRot,
						 DrawColor,
						 false,
						 DebugLifeTime);
	}
}

void AApplyRadialDamage::DebugCapsule()
{
}
