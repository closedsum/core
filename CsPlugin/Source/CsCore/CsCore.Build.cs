// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using UnrealBuildTool;
using System.IO;

public class CsCore : ModuleRules
{
    public CsCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        bUseUnity = false; // System.Environment.ProcessorCount < 64;

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        //PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "AssetRegistry",
                    "Json",
                    "JsonUtilities",
                    "DeveloperSettings",
                    "EnhancedInput", // TODO: Eventually move associated to plugin
                    "PhysicsCore",
                    "Niagara" // TODO: Eventually move associated to plugin
                }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Engine",
                "InputCore"
            }
        );

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "DeveloperToolSettings",
                    "RHI", // May need to breakout into plugin
                    "RenderCore", // TODO: Move associated code to plugin      
                    "ApplicationCore"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd"
                }
            );
        }
    }
}