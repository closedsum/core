// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using System.IO;
using UnrealBuildTool;

public class CsFX : ModuleRules
{
    public CsFX(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        bUseUnity = false;// System.Environment.ProcessorCount < 64;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "DeveloperSettings",
                    "CsCore",
                    "Niagara",
                    "NiagaraCore"
,                }
            );

        PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "Niagara"
                }
            );

        string engine_path = Path.GetFullPath(Target.RelativeEnginePath);
        string niagara_source_path = engine_path + "Plugins/FX/Niagara/Source/";

        PrivateIncludePaths.AddRange(
            new string[] {
                niagara_source_path + "Niagara/Private",
            }
        );

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "PhysicsCore"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                }
            );
        }
    }
}