// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseHitscan.generated.h"

UCLASS()
class MYROGUELIKE_API ABaseHitscan : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseHitscan();

	void Fire();
	void DebugLineTraceTick();
	void DebugLineTrace();

private:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	USkeletalMeshComponent *WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem *ImpactEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase *LaunchSound;
};
