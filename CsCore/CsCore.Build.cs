// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsCore : ModuleRules
{
    public CsCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        if (UEBuildConfiguration.bBuildEditor)
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