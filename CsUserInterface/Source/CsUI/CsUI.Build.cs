// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;

public class CsUI : ModuleRules
{
    public CsUI(ReadOnlyTargetRules Target) : base(Target)
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
                    "UMG",
                    "SlateCore",
                    "Slate",
                    "CsMacro",
                    "CsContainer",
                    "CsEnum",
                    "CsValid",
                    "CsScopedTimer",
                    "CsManager",
                    "CsTypes",
                    "CsCoreLibrary",
                    "CsConsoleCommand",
                    "CsTime",
                    "CsPool",
                    "CsData",
                    "CsUICore",
                    "CsPhysics", // TODO: Eventually remove dependency
                    "CsInput"
,                }
            );

       PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "InputCore",
                }
            );
    }
}