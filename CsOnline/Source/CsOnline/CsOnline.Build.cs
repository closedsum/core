// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsOnline : ModuleRules
{
    public CsOnline(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "OnlineSubsystem",
                    "OnlineSubsystemUtils",
                    "AssetRegistry",
                    "CsCore",
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