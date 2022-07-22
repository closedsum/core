// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class CsCore : ModuleRules
{
    public CsCore(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        bUseUnity = System.Environment.ProcessorCount < 64;

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
                    "PhysicsCore",
                    "HeadMountedDisplay",
                    "Niagara",
                }
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