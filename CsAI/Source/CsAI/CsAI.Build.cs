// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using UnrealBuildTool;

public class CsAI : ModuleRules
{
    public CsAI(ReadOnlyTargetRules Target) : base(Target)
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
                    "CsEnum",
                    "CsTypes",
                    "CsCoreLibrary",
                    "AIModule"
                }
            );

        /*
        PrivateDependencyModuleNames.AddRange(
            new string[] {
            }
        );
        */

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "GameplayTasks",
                    "NavigationSystem"
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