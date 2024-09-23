// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using System.IO;
using UnrealBuildTool;

public class CsJs : ModuleRules
{
    public CsJs(ReadOnlyTargetRules Target) : base(Target)
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
                    "V8",
                    "CsMacro",
                    "CsContainer",
                    "CsValid",
                    "CsPIE",
                    "CsManager",
                    "CsTypes",
                    "CsCoreLibrary",
                    "CsTime",
                    "CsCoroutine",
                    "CsData",
                    "CsInput"
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

        //string engine_path = Path.GetFullPath(Target.);
        //string v8_source_path = engine_path + "Plugins/FX/Niagara/Source/";

        //PrivateIncludePaths.AddRange(
        //    new string[] {
        //                niagara_source_path + "Niagara/Private",
        //    }
        //);

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "V8",
                    "InputCore",
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