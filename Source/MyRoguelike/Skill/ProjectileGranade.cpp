// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileGranade.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AProjectileGranade::AProjectileGranade()
{
}

void AProjectileGranade::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileGranade::OnHit);
}

void AProjectileGranade::OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
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
		// UGameplayStatics::ApplyPointDamage(HitActor, Damage, HitActor->GetActorLocation(), HitResult, OwnerController, OwnerPawn, nullptr);
		UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, TArray<AActor *>(), this, OwnerController, false, ECC_WorldStatic);
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
