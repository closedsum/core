// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsUI : ModuleRules
{
    public CsUI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "AssetRegistry",
                    "DeveloperSettings",
                    "CsCore",
                    "UMG",
                    "SlateCore"
,                }
            );

       PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "InputCore",
                }
            );
    }
}