// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsCc : ModuleRules
{
    public CsCc(ReadOnlyTargetRules Target) : base(Target)
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
                    "CsCore",
                }
            );

            /*
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "BlueprintGraph",
                }
            );
            */
        }
        else
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "AssetRegistry",
                    "CsCore",
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