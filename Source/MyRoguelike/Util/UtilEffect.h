// Copyright GuardiansW. All Rights Reserved.
//
// 이펙트 관련 편의 함수 모음


#pragma once


class AActor;
class USceneComponent;
class UNiagaraComponent;
class UNiagaraSystem;


namespace UtilEffect
{
	// 데코레이터를 발동한다.
	void ActivateDecorator( AActor* InActor, EDecorateUseType InUseType );

	// 파티클을 생성한다.
	UNiagaraComponent* SpawnParticleComponent( TSoftObjectPtr<UNiagaraSystem> InNiagaraSystem, const FVector& InLocation = FVector::ZeroVector, const FRotator& InRotation = FRotator::ZeroRotator, const FVector& InScale = FVector::OneVector, UWorld* InWorld = nullptr );

	// 파티클을 생성하고 부착한다.
	UNiagaraComponent* SpawnParticleComponentAttached( TSoftObjectPtr<UNiagaraSystem> InNiagaraSystem, USceneComponent* InAttachComp, FName InSocketName = NAME_None, const FVector& InLocation = FVector::ZeroVector, const FRotator& InRotation = FRotator::ZeroRotator, const FVector& InScale = FVector::OneVector );
}