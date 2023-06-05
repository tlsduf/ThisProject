// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHitscan.h"

#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <DrawDebugHelpers.h>
#include <GameFramework/Character.h>

// Sets default values
ABaseHitscan::ABaseHitscan()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);
}

void ABaseHitscan::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseHitscan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseHitscan::Fire()
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return;
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
		return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
	if (HasHit)
	{
		FVector ShotDirection = -Rotation.Vector();
		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShotDirection.Rotation());
		}
		AActor *HitActor = HitResult.GetActor();
		if (HitActor != nullptr)
		{
			UGameplayStatics::ApplyPointDamage(HitActor, Damage, HitActor->GetActorLocation(), HitResult, OwnerController, OwnerPawn, nullptr);
		}
	}

	if (MuzzleFlash)
	{
		ACharacter *MyCharacter = Cast<ACharacter>(GetOwner());
		USkeletalMeshComponent *OwnerMesh = MyCharacter->GetMesh();
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, OwnerMesh, TEXT("Muzzle_01"));
	}
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void ABaseHitscan::DebugLineTraceTick()
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return;
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
		return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
	if (HasHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, 0, -1.f); // HitPoint
	}
	DrawDebugLine(GetWorld(), Location, End, FColor::Red, 0, -1.f);	 // Line
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, 0, -1.f); // 사거리 끝
																	 // DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, 0, -1.f);
}

void ABaseHitscan::DebugLineTrace()
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return;
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
		return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	bool HasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
	if (HasHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, 0, 3.f); // HitPoint
	}
	DrawDebugLine(GetWorld(), Location, End, FColor::Red, 0, 3.f);	// Line
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, 0, 3.f); // 사거리 끝
	DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, 0, 3.f);
}
