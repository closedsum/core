// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsCore : ModuleRules
{
    public CsCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "OnlineSubsystem",
                    "OnlineSubsystemUtils",
                    "AssetRegistry",
                    "AIModule",
                    "GameplayTasks",
                    "Json",
                    "JsonUtilities",
                    "UMG",
                    "UnrealEd",
                    "AssetTools",
                    "ContentBrowser",
                    "SourceControl",
                    "Slate",
                    "EditorStyle",
                    "HeadMountedDisplay",
                    "V8",
                    "AnimationCore",
                    "Sequencer",
                    "LevelSequence",
                    "NavigationSystem",
                    "MovieScene",
                    "MovieSceneTracks",
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "BlueprintGraph",
                    "LevelSequenceEditor",
                }
            );
        }
        else
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "OnlineSubsystem",
                    "OnlineSubsystemUtils",
                    "AssetRegistry",
                    "AIModule",
                    "GameplayTasks",
                    "Json",
                    "JsonUtilities",
                    "UMG",
                    "HeadMountedDisplay",
                    "V8",
                    "LevelSequence",
                    "NavigationSystem",
                }
            );
        }

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "InputCore",
                "Slate",
                "SlateCore",
                "Json",
            }
        );
    }
}