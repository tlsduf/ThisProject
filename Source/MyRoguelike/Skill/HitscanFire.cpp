// Fill out your copyright notice in the Description page of Project Settings.

#include "HitscanFire.h"
#include "SkillActor/HitscanBase.h"
#include "../MyRoguelike.h"
#include "../Character/MyRoguelikeCharacter.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Character.h>

void UHitscanFire::BeginPlay()
{
	Super::BeginPlay();
	

}

void UHitscanFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHitscanFire::SkillTriggered()
{
	Super::SkillTriggered();

	Hitscan = GameGetWorld(this)->SpawnActor<AHitscanBase>(HitscanClass);
	Hitscan->SetOwner(Cast<AMyRoguelikeCharacter>(GetOwner()));
	Hitscan->Fire(Damage, MaxRange);
	if(DebugOnOff)
	{
		Hitscan->DebugLineTrace(MaxRange);
	}
	Hitscan->SelfDestroy();
}
