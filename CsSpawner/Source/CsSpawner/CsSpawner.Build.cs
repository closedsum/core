// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using UnrealBuildTool;

public class CsSpawner : ModuleRules
{
    public CsSpawner(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        bUseUnity = false;// System.Environment.ProcessorCount < 64;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "CsMacro",
                    "CsContainer",
                    "CsEnum",
                    "CsValid",
                    "CsManager",
                    "CsTypes",
                    "CsCoreLibrary",
                    "CsTime",
                    "CsCoroutine",
                    "CsModifier",
                    "CsCore"
                }
            );

       PrivateDependencyModuleNames.AddRange(
                new string[] {
                }
            );
    }
}