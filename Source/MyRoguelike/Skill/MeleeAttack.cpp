// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeAttack.h"
#include "SkillActor/ApplyRadialDamage.h"
#include "../MyRoguelike.h"
#include "../Character/MyRoguelikeCharacter.h"
#include "../Util/UtilCollision.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>

void UMeleeAttack::BeginPlay()
{
	Super::BeginPlay();
}

void UMeleeAttack::SkillTriggered()
{
	Super::SkillTriggered();

	ApplyCapsuleDamage(Cast<APawn>(GetOwner()), Damage, AttackRadius, AttackStartPoint, AttackRange, DebugOnOff);
}
