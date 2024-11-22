// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlatformerGame : ModuleRules
{
	public PlatformerGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "Public/PlatformerGame.h";

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore", 
               	"GameMenuBuilder",
                "HTTP",
                "CML",
				"WordPressForGaming",
				"WordPressContact",
				"WordPressServer"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[] {
			}
		); 

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Slate",
				"SlateCore",
			}
		);

        PrivateIncludePaths.AddRange(new string[] { 
			});
	}
}
