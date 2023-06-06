// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeAttack.h"
#include "SkillActor/ApplyRadialDamage.h"
#include "../MyRoguelike.h"
#include "../Character/MyRoguelikeCharacter.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>

void UMeleeAttack::BeginPlay()
{
	Super::BeginPlay();


}

void UMeleeAttack::SkillTriggered()
{
	Super::SkillTriggered();

	Melee = GameGetWorld(this)->SpawnActor<AApplyRadialDamage>(MeleeClass);
	Melee->SetOwner(Cast<AMyRoguelikeCharacter>(GetOwner()));
	Melee->AttackCheck(Damage, AttackRange, AttackRadius, DebugOnOff);
	Melee->SelfDestroy();
}
