// Copyright ubyte digital. All Right Reserved. https://ubyte.dev

using UnrealBuildTool;

public class GameplayLocationRuntime : ModuleRules
{
	public GameplayLocationRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"GameplayTags"
			}
			);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine"
			}
			);
	}
}
