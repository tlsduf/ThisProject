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

	// applydamage 프레임워크 ApplyRadialDamage 의 경우 구의 반지름
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float RadialDamageRadius = 500.f;
	// applydamage 프레임워크 ApplyRadialDamage 의 경우 중심에서 멀어질수록 약해지는 데미지를 입힐지말지
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	bool DoFullDamage = true;
	
	// 소유한 액터의 위치와 캡슐이 스윕을 시작하는 위치 사이의 거리
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float AttackStartPoint = 0.f;

	// 스윕이 시작하는 위치와 스윕이 끝나는 위치 사이의 거리
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float AttackRange = 50.f;

	// 캡슐의 반지름
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float AttackRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	bool DebugOnOff = false;

	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	bool DoRadialDamage = false;

protected:
	// 오버랩시 호출해서 데미지 적용, 투사체 파괴 등을 수행
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult);

	// OnHit의 실질적인 기능을 담고있는 함수 // OnHit이 상속이안됨.
	virtual void _OnHit(UPrimitiveComponent *HitComp, AActor *HitActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult);
};
