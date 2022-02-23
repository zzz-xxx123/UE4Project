// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IdNDemo : ModuleRules
{
	public IdNDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay" ,
			"SimpleNetChannel",
			"SimpleThread",
			"NetGameCommon",
            "Slate",
            "SlateCore",
        });
	}
}
