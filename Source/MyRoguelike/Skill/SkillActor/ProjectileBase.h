// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

// class USoundBase;

UCLASS()
class MYROGUELIKE_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "MyCustomCategory")
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyCustomCategory")
	class UProjectileMovementComponent *ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UParticleSystem *MuzzleParticles;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UParticleSystem *HitParticles;

	UPROPERTY(VisibleAnywhere, Category = "MyCustomCategory")
	class UParticleSystemComponent *TrailParticles;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	USoundBase *MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	USoundBase *HitSound;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float RadialDamageRadius = 500.f;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	bool DoFullDamage = true;
};
