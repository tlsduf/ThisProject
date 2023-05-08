// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileMissile.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AProjectileMissile::AProjectileMissile()
{
}

void AProjectileMissile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileMissile::OnHit);
}

void AProjectileMissile::OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
{
	AActor *OwnerPawn = Cast<APawn>(GetOwner());
	AController *OwnerController = OwnerPawn->GetInstigatorController();
	if (OwnerPawn == nullptr)
	{
		Destroy();
		return;
	}

	Destroy();
	if (HitActor && HitActor != this && HitActor != OwnerPawn)
	{
		// UGameplayStatics::ApplyDamage(HitActor, Damage, OwnerController, this, nullptr);
		UGameplayStatics::ApplyPointDamage(HitActor, Damage, HitActor->GetActorLocation(), HitResult, OwnerController, OwnerPawn, nullptr);
		// UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), 350.f, nullptr, TArray<AActor *>(), this, OwnerController, false, ECC_Visibility);
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
		}
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
}