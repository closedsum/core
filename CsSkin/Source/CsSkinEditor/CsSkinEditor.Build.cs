// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using UnrealBuildTool;

public class CsSkinEditor : ModuleRules
{
    public CsSkinEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        bUseUnity = false;// System.Environment.ProcessorCount < 64;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
            }
        );

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "UnrealEd",
                    "CsCore",
                    "CsEditor",
                    "CsSkin"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                }
            );
        }
    }
}