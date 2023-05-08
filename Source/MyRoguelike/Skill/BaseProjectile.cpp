// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	// ProjectileMesh->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
void ABaseProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
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
		//UGameplayStatics::ApplyDamage(HitActor, Damage, OwnerController, this, nullptr);
		//UGameplayStatics::ApplyPointDamage(HitActor, Damage, HitActor->GetActorLocation(), HitResult, OwnerController, OwnerPawn, nullptr);
		UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), 350.f, nullptr, TArray<AActor *>(), this, OwnerController, false, ECC_Visibility);
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
}*/