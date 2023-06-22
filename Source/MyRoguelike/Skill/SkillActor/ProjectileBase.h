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
	
	// 충돌을 담당하는 캡슐
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	class UCapsuleComponent *CapsuleComponent;

	// 외형만 보여주는 메쉬
	UPROPERTY(EditDefaultsOnly, Category = "MyCustomCategory")
	UStaticMeshComponent *ProjectileMesh;

	// UProjectileMovementComponent 투사체의 움직임을 제어해주는 언리얼함수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyCustomCategory")
	class UProjectileMovementComponent *ProjectileMovementComponent;

	// 투사체 생성-발사 이펙트 // 생성 이펙트와 발사이펙트를 Base에 구분할 것인가? 생성이펙트가 필요하다면 자손클래스에서 따로 할당할 것인지
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UParticleSystem *ShotParticles;

	// 투사체 hit 이펙트 // 파괴 시 이펙트와 오버랩이벤트의 이펙트를 따로 해야하는지
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	UParticleSystem *HitParticles;

	// 트레일파티클
	UPROPERTY(VisibleAnywhere, Category = "MyCustomCategory")
	class UParticleSystemComponent *TrailParticles;

	// 발사 사운드
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	USoundBase *ShotSound;
	
	// hit 사운드
	UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	USoundBase *HitSound;

	//UPROPERTY(EditAnywhere, Category = "MyCustomCategory")
	//TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

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

	// 데미지 // 데이터테이블에서 이곳으로 값을 받아올 것인
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

	UFUNCTION()
	void BeginOverlapEvent(class UPrimitiveComponent* InHitComp, class AActor* InOtherActor, class UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, bool InbFromSweep, const FHitResult & InSweepResult);

	virtual void _BeginOverlapEvent(class UPrimitiveComponent* InHitComp, class AActor* InOtherActor, class UPrimitiveComponent* InOtherComp, int32 InOtherBodyIndex, bool InbFromSweep, const FHitResult & InSweepResult);
};
