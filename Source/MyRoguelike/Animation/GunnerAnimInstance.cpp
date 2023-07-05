// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerAnimInstance.h"
#include "../Util/UtilEnum.h"


#include <Animation/AnimMontage.h>

// 틱마다 호출되는 함수
UGunnerAnimInstance::UGunnerAnimInstance()
	:ShiftMontage(nullptr), SkillQMontage(nullptr), SkillEMontage(nullptr), SkillRMontage(nullptr), HandLAlpha(0.f), HandRAlpha(0.f), AlphaAnimatorHandL(), AlphaAnimatorHandR()
{
}

void UGunnerAnimInstance::NativeUpdateAnimation(float InDeltaSeconds)
{
	Super::NativeUpdateAnimation(InDeltaSeconds);

	AlphaAnimatorHandL.Update(InDeltaSeconds);
	AlphaAnimatorHandR.Update(InDeltaSeconds);
}

// AbilityType에 따른 몽타주를 반환합니다. None입력시 기본 몽타주 반환
UAnimMontage* UGunnerAnimInstance::GetMontageByAbilityType(EAbilityType InAbilityType)
{
	switch ( InAbilityType )
	{
		case EAbilityType::MouseLM:			return nullptr;
		case EAbilityType::MouseRM:			return nullptr;
		case EAbilityType::Shift:			return LoadSoftObject<UAnimMontage>(ShiftMontage);
		case EAbilityType::SkillQ:			return LoadSoftObject<UAnimMontage>(SkillQMontage);
		case EAbilityType::SkillE:			return LoadSoftObject<UAnimMontage>(SkillEMontage);
		case EAbilityType::SkillR:			return LoadSoftObject<UAnimMontage>(SkillRMontage);
		case EAbilityType::None:			return nullptr;
	}

	return nullptr;
}

// 몽타주를 재생합니다.
float UGunnerAnimInstance::PlayMontage(EAbilityType InAbilityType, EAroundSkillMontageType InSectionType, float InPlayRate/* = 1.f*/)
{
	UAnimMontage* animMontage = GetMontageByAbilityType(InAbilityType);
	if (!animMontage)
		return 0.f;

	//TODO InSectionType 고쳐야됨 근데 Default로 읽어지긴하는듯?
	FName sectionName = *ENUM_TO_STRING( EAroundSkillMontageType, InSectionType );
	Montage_Play(animMontage, InPlayRate);
	Montage_JumpToSection(sectionName, animMontage);
	
	return animMontage->GetSectionLength(animMontage->GetSectionIndex(sectionName));
}
// 몽타주 재생을 정지합니다.
void UGunnerAnimInstance::StopMontage(EAbilityType InAbilityType, float InBlendOutTime)
{
	UAnimMontage* animMontage = GetMontageByAbilityType(InAbilityType);
	if(!animMontage)
		return;
	Montage_Stop(InBlendOutTime, animMontage);
}

// 몽타주 재생을 일시 정지합니다.
void UGunnerAnimInstance::PauseMontage(EAbilityType InAbilityType)
{
	UAnimMontage* animMontage = GetMontageByAbilityType(InAbilityType);
	if(!animMontage)
		return;
	Montage_Pause(animMontage);
}

// 몽타주를 다시 재생합니다.
void UGunnerAnimInstance::ResumeMontage(EAbilityType InAbilityType)
{
	UAnimMontage* animMontage = GetMontageByAbilityType(InAbilityType);
	if(!animMontage)
		return;
	Montage_Resume(animMontage);
}

void UGunnerAnimInstance::RotateHandL()
{
	AnimatorParam param;
	param.AnimType = EAnimType::QuadraticEaseInOut;
	param.StartValue = 1.f;
	param.EndValue = 0.f;
	param.DurationTime = 0.3f;

	TWeakObjectPtr<UGunnerAnimInstance> thisPtr = this;
	param.DurationFunc = [thisPtr](float InCurValue)
	{
		if(thisPtr.IsValid())
		thisPtr->HandLAlpha = InCurValue;
	};
	
	AlphaAnimatorHandL.Start(param);
}
	
void UGunnerAnimInstance::RotateHandR()
{
	AnimatorParam param;
	param.AnimType = EAnimType::QuadraticEaseInOut;
	param.StartValue = 1.f;
	param.EndValue = 0.f;
	param.DurationTime = 0.3f;

	TWeakObjectPtr<UGunnerAnimInstance> thisPtr = this;
	param.DurationFunc = [thisPtr](float InCurValue)
	{
		if(thisPtr.IsValid())
			thisPtr->HandRAlpha = InCurValue;
	};
	
	AlphaAnimatorHandR.Start(param);
}
