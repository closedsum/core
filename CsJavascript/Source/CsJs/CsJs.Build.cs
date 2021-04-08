// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsJs : ModuleRules
{
    public CsJs(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "AssetRegistry",
                    "CsCore",
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
                    "V8",
                }
            );

            /*
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                }
            );
            */
        }
    }
}