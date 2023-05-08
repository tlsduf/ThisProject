// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class USoundBase;

UCLASS()
class MYROGUELIKE_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	class UProjectileMovementComponent *ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	//UFUNCTION()
	//virtual void OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult);

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem *HitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent *TrailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase *LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
