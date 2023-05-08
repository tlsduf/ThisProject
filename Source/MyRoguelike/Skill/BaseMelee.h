// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMelee.generated.h"

UCLASS()
class MYROGUELIKE_API ABaseMelee : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseMelee();

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

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	USkeletalMeshComponent *WeaponMesh;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Melee, Meta = (AllowPrivateAccess = true))
    float AttackRange;
    
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Melee, Meta = (AllowPrivateAccess = true))
    float AttackRadius;

	UPROPERTY(EditAnywhere)
    float Damage = 10.f;

};
