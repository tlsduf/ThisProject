// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "../Common/GameLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SkillBase)

// Sets default values for this component's properties
USkillBase::USkillBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkillBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillBase::SkillStarted()
{
	//LOG_SCREEN(TEXT("%s, SkillStarted!"), *GetName());
}

void USkillBase::SkillOngoing()
{
	//LOG_SCREEN(TEXT("%s, SkillOngoing!"), *GetName());
}

void USkillBase::SkillTriggered()
{
	//LOG_SCREEN(TEXT("%s, SkillTriggered!"), *GetName());
}

void USkillBase::SkillCompleted()
{
	//LOG_SCREEN(TEXT("%s, SkillCompleted!"), *GetName());

	// 테스트용 코드입니다. 실제 완료과 입력 완료는 다르니 구분해야합니다.
	//SkillCompletedDelegate.Execute(ESkillCompletedType::Success);
}

void USkillBase::SkillCanceled()
{
	//LOG_SCREEN(TEXT("%s, SkillCanceled!"), *GetName());

	// 테스트용 코드입니다. 실제 캔슬과 입력 캔슬은 다르니 구분해야합니다.
	//SkillCompletedDelegate.Execute(ESkillCompletedType::Canceled);
}