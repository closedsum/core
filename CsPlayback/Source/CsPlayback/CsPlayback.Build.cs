// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using UnrealBuildTool;

public class CsPlayback : ModuleRules
{
    public CsPlayback(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        bUseUnity = false;// System.Environment.ProcessorCount < 64;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "AssetRegistry",
                    "Json",
                    "JsonUtilities",
                    "CsCore",
                    "CsThread"
                }
            );

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

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                }
            );

            /*
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                }
            );
            */
        }
        else
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                }
            );
        }
    }
}