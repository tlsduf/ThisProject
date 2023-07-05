// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "GunnerAnimInstance.generated.h"

enum class EAroundSkillMontageType : uint8;

UCLASS()
class MYROGUELIKE_API UGunnerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	// 캐릭터가 사용할 애님 몽타주 Shift
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UAnimMontage> ShiftMontage;
	
	// 캐릭터가 사용할 애님 몽타주 SkillQ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UAnimMontage> SkillQMontage;
	
	// 캐릭터가 사용할 애님 몽타주 SkillE
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UAnimMontage> SkillEMontage;

	// 캐릭터가 사용할 애님 몽타주 SkillR
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UAnimMontage> SkillRMontage;
	
	// HandL 본 회전 블렌딩 알파
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float HandLAlpha;
	
	// HandR 본 회전 블렌딩 알파
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float HandRAlpha;

	// HandL 알파 값을 애니메이팅 합니다.
	Animator AlphaAnimatorHandL;

	// HandR 알파 값을 애니메이팅 합니다.
	Animator AlphaAnimatorHandR;
public:
	// 생성자
	UGunnerAnimInstance();
	// 틱마다 호출되는 함수, 스피드를 계산한다.
	virtual void NativeUpdateAnimation(float InDeltaSeconds) override;
	// AbilityType에 따른 몽타주를 반환합니다. None입력시 기본 몽타주 반환
	UAnimMontage* GetMontageByAbilityType(EAbilityType InAbilityType);
	// 몽타주를 재생하고 DurationTime을 반환합니다.
	float PlayMontage(EAbilityType InAbilityType, EAroundSkillMontageType InSectionType, float InPlayRate = 1.f);
	// 몽타주 재생을 정지합니다.
	void StopMontage(EAbilityType InAbilityType, float InBlendOutTime);
	// 몽타주 재생을 일시 정지합니다.
	void PauseMontage(EAbilityType InAbilityType);
	// 몽타주를 다시 재생합니다.
	void ResumeMontage(EAbilityType InAbilityType);
	// 왼쪽 손목 반동재생
	void RotateHandL();
	// 오른쪽 손목 반동재생
	void RotateHandR();
};

// AroundSkill 몽타주
UENUM()
enum class EAroundSkillMontageType : uint8
{
	AroundAttack1,				// 첫 번 째 콤보공격
	AroundAttack1ToIdle,		// 입력초과시 준비자세로 이어지는 시퀀스
	AroundAttack2,				// 두 번 째 콤보공격
	AroundAttack2ToIdle,		// 입력초과시 준비자세로 이어지는 시퀀스
	AroundAttack3,				// 세 번 째 콤보공격
	AroundAttack3ToIdle,		// 입력초과시 준비자세로 이어지는 시퀀스
	AroundAttack4,				// 네 번 째 콤보공격 (마지막)
	AroundAttack4ToIdle,		// 입력초과시 준비자세로 이어지는 시퀀스
	ToIdle,						// 네 번 째 콤보공격에서 준비자세로 이어지는 시퀀스
	Max
};