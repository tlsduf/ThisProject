// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyRoguelike : ModuleRules
{
	public MyRoguelike(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "MyRoguelike.h";

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" , "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayTasks", "UMG" });
	}
}
