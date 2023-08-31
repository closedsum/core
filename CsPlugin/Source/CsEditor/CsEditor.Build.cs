// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsEditor : ModuleRules
{
    public CsEditor(ReadOnlyTargetRules Target) : base(Target)
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
                    "Niagara",
                    "CsCore",
                }
            );

       PrivateDependencyModuleNames.AddRange(
            new string[] {
                "InputCore",
                "Slate",
                "SlateCore",
            }
        );

        if (Target.Type == TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd",
                    "AssetTools",
                    "ContentBrowser",
                    "BlueprintGraph",
                    "Slate",
                    "PropertyEditor",
                    "GraphEditor",
                    "EditorStyle",
                    "NiagaraEditor",
                    "DeveloperToolSettings"
                }
            );
        }
        else
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                }
            );
        }
    }
}