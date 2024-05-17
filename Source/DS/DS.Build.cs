// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DS : ModuleRules
{
	public DS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "GameplayTags", "GameplayTasks", "UMG", "AIModule"});
	}
}
