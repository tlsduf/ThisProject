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

	UPROPERTY(VisibleAnywhere, Category = "MyCustomCategory")
	USkeletalMeshComponent *WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UParticleSystem *ImpactEffect;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	class USoundBase *LaunchSound;
};
