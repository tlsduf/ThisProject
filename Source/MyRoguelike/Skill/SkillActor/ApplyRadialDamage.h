// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ApplyRadialDamage.generated.h"

UCLASS()
class MYROGUELIKE_API AApplyRadialDamage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AApplyRadialDamage();

	void AttackCheck();
	void DebugCapsule();
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
    float AttackRange;
    
    UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
    float AttackRadius;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
    float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	bool DebugOnOff = false;

};
