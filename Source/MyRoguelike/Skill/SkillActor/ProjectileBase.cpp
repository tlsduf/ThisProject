// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "../../Util/UtilCollision.h"

#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>


// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(44.f, 60.f);
	SetRootComponent(CapsuleComponent);
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(CapsuleComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	APawn *ownerPawn = Cast<APawn>(GetOwner());
	if (ShotParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShotParticles, GetActorLocation(), GetActorRotation());
	}
	if(ShotAttachParticles)
	{
		UGameplayStatics::SpawnEmitterAttached(ShotAttachParticles, GetRootComponent(), "null", FVector(0), FRotator::ZeroRotator, FVector(1), EAttachLocation::KeepRelativeOffset, true);
	}
	if (ShotSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShotSound, GetActorLocation());
	}
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// _OnHit 호출용으로 사용
void AProjectileBase::OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
{
	_OnHit(HitComp, HitActor, OtherComp, NormalImpulse, HitResult);
}

// 히트시 호출해서 데미지 적용, 투사체 파괴 등을 수행
void AProjectileBase::_OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult)
{
	APawn *ownerPawn = Cast<APawn>(GetOwner());
	AController *ownerController = ownerPawn->GetController();
	if (ownerPawn == nullptr)
	{
		Destroy();
		return;
	}

	//TODO 리펙토링 해야될듯
	Destroy();
	if (HitActor && HitActor != this && HitActor != ownerPawn)
	{
		if(DoRadialDamage)
		{
			TArray<FHitResult> sweepResults;
			FVector startLocation = GetActorLocation() + GetActorForwardVector() * AttackStartPoint;
			FVector endLocation = startLocation + GetActorForwardVector() * AttackRange;
			UtilCollision::CapsuleSweepMulti(sweepResults, startLocation, endLocation, AttackRadius, DebugOnOff);
			if(!sweepResults.IsEmpty())
			{
				for (auto It = sweepResults.CreateIterator(); It; It++)
				{
					HitActor = It->GetActor();
					UGameplayStatics::ApplyDamage(HitActor, Damage, ownerController, ownerPawn, nullptr);
				}
			}
		}
		else
		{
			UGameplayStatics::ApplyDamage(HitActor, Damage, ownerController, ownerPawn, nullptr);
			// UGameplayStatics::ApplyPointDamage(HitActor, Damage, HitActor->GetActorLocation(), HitResult, ownerController, OwnerPawn, nullptr);
			// UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), RadialDamageRadius, nullptr, TArray<AActor *>(), this, ownerController, DoFullDamage, ECC_WorldStatic);
		}
	}
	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
	}
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	/*
	if (HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
	*/
}

void AProjectileBase::BeginOverlapEvent(class UPrimitiveComponent* InHitComp, class AActor* InOtherActor, class UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, bool InbFromSweep, const FHitResult & InSweepResult)
{
	_BeginOverlapEvent(InHitComp, InOtherActor, InOtherComp, InOtherBodyIndex, InbFromSweep, InSweepResult);
}

void AProjectileBase::_BeginOverlapEvent(class UPrimitiveComponent* InHitComp, class AActor* InOtherActor, class UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, bool InbFromSweep, const FHitResult & InSweepResult)
{
	auto *ownerPawn = Cast<APawn>(GetOwner());
	auto *ownerController = ownerPawn->GetController();
	
	//UtilEffect::ActivateDecorator( this, EDecorateUseType::Despawn);
	
	if (ownerPawn == nullptr)
	{
		Destroy();
		return;
	}

	Destroy();
	if (InOtherActor != nullptr && InOtherActor != ownerPawn)
	{
		if(DoRadialDamage)
		{
			TArray<FHitResult> sweepResults;
			FVector startLocation = GetActorLocation() + GetActorForwardVector() * AttackStartPoint;
			FVector endLocation = startLocation + GetActorForwardVector() * AttackRange;
			UtilCollision::CapsuleSweepMulti(sweepResults, startLocation, endLocation, AttackRadius, DebugOnOff);
			for (auto It = sweepResults.CreateIterator(); It; It++)
			{
				InOtherActor = It->GetActor();
				UGameplayStatics::ApplyDamage(InOtherActor, Damage, ownerController, ownerPawn, nullptr);
			}
		}
		else
		{
			UGameplayStatics::ApplyDamage(InOtherActor, Damage, ownerController, ownerPawn, nullptr);
			// UGameplayStatics::ApplyPointDamage(HitActor, Damage, HitActor->GetActorLocation(), HitResult, ownerController, OwnerPawn, nullptr);
			// UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), RadialDamageRadius, nullptr, TArray<AActor *>(), this, ownerController, DoFullDamage, ECC_WorldStatic);
		}
	}
	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
	}
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
}