// Fill out your copyright notice in the Description page of Project Settings.

#include "RoguelikePlayerController.h"
#include "Blueprint/UserWidget.h"

#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputMappingContext.h>

#include "../Skillbase.h"
#include "../Character/MyRoguelikeCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(RoguelikePlayerController)

void ARoguelikePlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(MappingContext, 0);
    }

    /*
        Menu = CreateWidget(this, UIMenuClass);
        if (Menu != nullptr)
        {
            Menu->AddToViewport();
        }
        SetShowMouseCursor(true);
        GetPawn()->DisableInput(this);*/

    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

void ARoguelikePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARoguelikePlayerController::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARoguelikePlayerController::StopJumping);

        EnhancedInputComponent->BindAction(InputC, ETriggerEvent::Started, this, &ARoguelikePlayerController::ToggleJog);
        EnhancedInputComponent->BindAction(InputW, ETriggerEvent::Started, this, &ARoguelikePlayerController::WPressed);
        EnhancedInputComponent->BindAction(InputW, ETriggerEvent::Completed, this, &ARoguelikePlayerController::WReleased);

        EnhancedInputComponent->BindAction(MouseWheelUp, ETriggerEvent::Started, this, &ARoguelikePlayerController::SetZoomInProp);
        EnhancedInputComponent->BindAction(MouseWheelDown, ETriggerEvent::Started, this, &ARoguelikePlayerController::SetZoomOutProp);

        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARoguelikePlayerController::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARoguelikePlayerController::Look);

        //스킬 호출에 관한 바인딩
        for (uint8 i = 0; i < SkillInputActions.Num(); ++i)
        {
        EnhancedInputComponent->BindAction(SkillInputActions[i], ETriggerEvent::Started, this, &ARoguelikePlayerController::OnInputSkillStarted);
        EnhancedInputComponent->BindAction(SkillInputActions[i], ETriggerEvent::Ongoing, this, &ARoguelikePlayerController::OnInputSkillOngoing);
        EnhancedInputComponent->BindAction(SkillInputActions[i], ETriggerEvent::Triggered, this, &ARoguelikePlayerController::OnInputSkillTriggered);
        EnhancedInputComponent->BindAction(SkillInputActions[i], ETriggerEvent::Completed, this, &ARoguelikePlayerController::OnInputSkillCompleted);
        EnhancedInputComponent->BindAction(SkillInputActions[i], ETriggerEvent::Canceled, this, &ARoguelikePlayerController::OnInputSkillCanceled);
        }
    }
}

// =============================================================
// 캐릭터가 포즈되었을때 호출됩니다.
// 캐릭터 변경 시스템을 위해 캐릭터가 변경되면, 바뀐 캐릭터의 스킬을 인스턴스화 시키고 trigger 타입을 리매핑합니다.
// =============================================================
void ARoguelikePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RemapSkillTriggerTypes();
}

void ARoguelikePlayerController::RemapSkillTriggerTypes()
{
	// 스킬에 관한 바인딩
	if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
	{
		character->InitSkills(); // TSubClassOf로 설정된 캐릭터의 스킬들을 인스턴스화 시킵니다.
		
		uint8 index = 0;
		while(index < character->GetSkills().Num() && index < SkillInputActions.Num())
		{
			// 설정해둔 트리거 타입을 넣습니다.
			SkillInputActions[index]->Triggers.Reset();
			SkillInputActions[index]->Triggers.Add(character->GetSkills()[index]->GetTriggerType());
			index++;
		}
	}
	
	// 추후 확인해야 할지도 모름.
	// If you have made changes to the triggers/modifiers associated with a UInputAction that was previously mapped a flush is required to reset the tracked data for that action.
	// 위에서 Trigger를 변경하여 리빌드 진행.
	if (UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subSystem->RequestRebuildControlMappings(FModifyContextOptions(), EInputMappingRebuildType::RebuildWithFlush);
	}
}

// =============================================================
// 입력된 ActionInput의 이름을 비교하여 몇번째 스킬인지 (Index)를 알아 내는 함수입니다.
// =============================================================
int8 ARoguelikePlayerController::GetSkillIndexFromAction(const FInputActionInstance& InInstance)
{
	if(const UInputAction* inputAction = InInstance.GetSourceAction())
	{
		if(inputAction->GetName().Contains(TEXT("LeftMouse")))
		{
			return 0;
		}
		else if(inputAction->GetName().Contains(TEXT("RightMouse")))
		{
			return 1;
		}
		else if(inputAction->GetName().Contains(TEXT("Shift")))
		{
			return 2;
		}
		else if(inputAction->GetName().Contains(TEXT("InputQ")))
		{
			return 3;
		}
		else if(inputAction->GetName().Contains(TEXT("InputE")))
		{
			return 4;
		}
        else if(inputAction->GetName().Contains(TEXT("InputR")))
		{
			return 5;
		}
	}
	return -1;
}

// =============================================================
// 스킬들에 대한 바인딩입니다. 각 스킬별로 Started, Ongoing, Triggered, Completed, Canceled에 대해 바인딩하며,
// 입력된 ActionInput의 이름을 비교하여 몇번 째 스킬인지 (Index)를 알아 낸 후,
// 호출할 index에 스킬이 들어 있는지 크기를 통해 확인하고,
// 캐릭터의 각 타입에 맞는 기능을 호출합니다.
// =============================================================
void ARoguelikePlayerController::OnInputSkillStarted(const FInputActionInstance& InInstance)
{
	if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
	{
		const int8 skillIndex = GetSkillIndexFromAction(InInstance);
		if(skillIndex > -1)
		{
			character->SkillStarted(skillIndex);
		}
	}
}

void ARoguelikePlayerController::OnInputSkillOngoing(const FInputActionInstance& InInstance)
{
	if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
	{
		const int8 skillIndex = GetSkillIndexFromAction(InInstance);
		if(skillIndex > -1)
		{
			character->SkillOngoing(skillIndex);
		}
	}
}

void ARoguelikePlayerController::OnInputSkillTriggered(const FInputActionInstance& InInstance)
{
	if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
	{
		const int8 skillIndex = GetSkillIndexFromAction(InInstance);
		if(skillIndex > -1)
		{
			character->SkillTriggered(skillIndex);
		}
	}
}

void ARoguelikePlayerController::OnInputSkillCompleted(const FInputActionInstance& InInstance)
{
	if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
	{
		const int8 skillIndex = GetSkillIndexFromAction(InInstance);
		if(skillIndex > -1)
		{
			character->SkillCompleted(skillIndex);
		}
	}
}

void ARoguelikePlayerController::OnInputSkillCanceled(const FInputActionInstance& InInstance)
{
	if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
	{
		const int8 skillIndex = GetSkillIndexFromAction(InInstance);
		if(skillIndex > -1)
		{
			character->SkillCanceled(skillIndex);
		}
	}
}


void ARoguelikePlayerController::Jump()
{
    if (ACharacter *character = Cast<ACharacter>(GetCharacter()))
    {
        character->Jump();
    }
}

void ARoguelikePlayerController::StopJumping()
{
    if (ACharacter *character = Cast<ACharacter>(GetCharacter()))
    {
        character->StopJumping();
    }
}

void ARoguelikePlayerController::ToggleJog()
{
    if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
    {
        character->Jog();
    }
}

void ARoguelikePlayerController::WPressed()
{
    if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
    {
        character->WPressed();
    }
}

void ARoguelikePlayerController::WReleased()
{
    if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
    {
        character->WReleased();
    }
}

void ARoguelikePlayerController::SetZoomInProp()
{
    if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
    {
        character->SetZoomInProp();
    }
}

void ARoguelikePlayerController::SetZoomOutProp()
{
    if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
    {
        character->SetZoomOutProp();
    }
}

void ARoguelikePlayerController::Move(const FInputActionValue &Value)
{
    if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
    {
        character->Move(Value);
    }
}

void ARoguelikePlayerController::Look(const FInputActionValue &Value)
{
    if (AMyRoguelikeCharacter *character = Cast<AMyRoguelikeCharacter>(GetCharacter()))
    {
        character->Look(Value);
    }
}

void ARoguelikePlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}