// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsEditor : ModuleRules
{
    public CsEditor(ReadOnlyTargetRules Target) : base(Target)
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
                    "Slate",
                    "V8",
                    "CsCore",
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
                    "V8",
                    "CsCore",
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