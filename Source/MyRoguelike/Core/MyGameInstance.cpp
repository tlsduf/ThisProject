// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

#include <Modules/ModuleManager.h>

UMyGameInstance::UMyGameInstance()
{
    static const FName PropertyEditor("PropertyEditor");
    FPropertyEditorModule &PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);

#define LOCTEXT_NAMESPACE "PropertySection"
    TSharedRef<FPropertySection> Section1 = PropertyModule.FindOrCreateSection("MyRoguelikeCharacter", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
    Section1->AddCategory("Defensive");
    Section1->AddCategory("Debug");
    Section1->AddCategory("BaseMovement");
    Section1->AddCategory("CombatProp");
    Section1->AddCategory("Skill");

    TSharedRef<FPropertySection> Section2 = PropertyModule.FindOrCreateSection("BasePlayerCharacter", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
    Section2->AddCategory("ThisMovement");
    Section2->AddCategory("LM");
    Section2->AddCategory("skill Q");
    Section2->AddCategory("skill E");
    Section2->AddCategory("skill R");

    // [[아래 카테고리들은 대충 뭉뚱그려서 관리 할 카테고리들임 (따로 관리하기에는 너무 종류가 많고 이름도 다 다름)]]
    // - 몬스터
    TSharedRef<FPropertySection> Section3 = PropertyModule.FindOrCreateSection("BaseEnemyCharacter", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
    Section3->AddCategory("MyCustomCategory");
    // - 스킬액터
    TSharedRef<FPropertySection> Section4 = PropertyModule.FindOrCreateSection("ApplyRadialDamage", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
    Section4->AddCategory("MyCustomCategory");
    TSharedRef<FPropertySection> Section5 = PropertyModule.FindOrCreateSection("BaseHitscan", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
    Section5->AddCategory("MyCustomCategory");
    TSharedRef<FPropertySection> Section6 = PropertyModule.FindOrCreateSection("ProjectileBase", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
    Section6->AddCategory("MyCustomCategory");
    // - 스킬로직
    TSharedRef<FPropertySection> Section7 = PropertyModule.FindOrCreateSection("SkillGunnerQ", "CustomSection", LOCTEXT("CustomSection", "CustomSection"));
    Section7->AddCategory("MyCustomCategory");
#undef LOCTEXT_NAMESPACE
}

UMyGameInstance::~UMyGameInstance()
{
}
