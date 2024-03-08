// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsSeq : ModuleRules
{
    public CsSeq(ReadOnlyTargetRules Target) : base(Target)
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
                    "MovieScene",
                    "MovieSceneTracks",
                    "LevelSequence"
                }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "LevelSequence"
            }
        );

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
    }
}