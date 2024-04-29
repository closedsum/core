// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsSeEditor : ModuleRules
{
    public CsSeEditor(ReadOnlyTargetRules Target) : base(Target)
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
                    "AssetRegistry",
                    "UnrealEd",
                    "AssetTools",
                    "ContentBrowser",
                    "BlueprintGraph",
                    "Slate",
                    "PropertyEditor",
                    "GraphEditor",
                    "EditorStyle",
                    "CsEnum",
                    "CsEnumEditor",
                    "CsSe",
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "Slate",
                    "SlateCore",
                }
            );
        }
    }
}