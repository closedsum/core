// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsAnimation : ModuleRules
{
    public CsAnimation(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "AssetRegistry",
                    "CsCore",
                }
            );

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd",
                    "AnimationCore",
                    "Sequencer",
                    "LevelSequence",
                    "MovieScene",
                    "MovieSceneTracks",
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "LevelSequenceEditor",
                }
            );
        }
        else
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "LevelSequence",
                }
            );
        }

        /*
        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "InputCore",
                "Slate",
                "SlateCore",
                "Json",
            }
        );
        */
    }
}