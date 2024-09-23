// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using UnrealBuildTool;

public class CsPerformance : ModuleRules
{
    public CsPerformance(ReadOnlyTargetRules Target) : base(Target)
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
                    "DeveloperSettings",
                    "RenderCore",
                    "CsMacro",
                    "CsContainer",
                    "CsValid",
                    "CsManager",
                    "CsTypes",
                    "CsCoreLibrary",
                    "UMG"
,                }
            );

       PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "InputCore",
                }
            );

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "SlateCore"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                }
            );
        }
    }
}