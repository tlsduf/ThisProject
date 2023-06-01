// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "RoguelikePlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputAction;
class UInputMappingContext;
struct FInputActionInstance;

UCLASS()
class MYROGUELIKE_API ARoguelikePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn *InPawn) override;

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext *MappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *LookAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *InputC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *InputW;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *MouseWheelUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *MouseWheelDown;

	// 6개의 스킬 InputAction // 순서대로 LM, RM, LShift, Q, E, R
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UInputAction>> SkillInputActions;

private:
	void Move(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);

	void Jump();
	void StopJumping();

	void ToggleJog();
	void WPressed();
	void WReleased();

	void SetZoomInProp();
	void SetZoomOutProp();

	// 스킬들의 트리거 타입을 변경. OnPosses에서 호출
	void RemapSkillTriggerTypes();

	// 입력된 ActionInput의 이름을 비교하여 몇번째 스킬인지 (Index)를 알아 내는 함수
	int8 GetSkillIndexFromAction(const FInputActionInstance &InInstance);

	// 스킬 관련 바인딩
	void OnInputSkillStarted(const FInputActionInstance &InInstance);
	void OnInputSkillOngoing(const FInputActionInstance &InInstance);
	void OnInputSkillTriggered(const FInputActionInstance &InInstance);
	void OnInputSkillCompleted(const FInputActionInstance &InInstance);
	void OnInputSkillCanceled(const FInputActionInstance &InInstance);

	void SetPlayerEnabledState(bool bPlayerEnabled);

private:
	UUserWidget *HUD;
	UUserWidget *Menu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> UIMenuClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;
};
