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

void AApplyRadialDamage::AttackCheck(float Damage, float AttackRange, float AttackRadius, bool DebugOnOff)
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	AController *OwnerController = OwnerPawn->GetInstigatorController();
	if (OwnerPawn == nullptr)
	{
		Destroy();
		return;
	}

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		OwnerPawn->GetActorLocation(),
		OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	AActor *HitActor = HitResult.GetActor();
	if (HasHit)
	{
		if (HitActor != nullptr && HitActor != OwnerPawn)
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
		FColor DrawColor = (HitActor != nullptr) ? FColor::Green : FColor::Red;
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

void AApplyRadialDamage::SelfDestroy()
{
	if (this != nullptr)
	{
		Destroy();
	}
}