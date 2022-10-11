// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

using UnrealBuildTool;

public class GameplayLocationEditor : ModuleRules
{
	public GameplayLocationEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "EditorSubsystem" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Engine", "GameplayLocationRuntime" });
	}
}
