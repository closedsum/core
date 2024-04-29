// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using UnrealBuildTool;
using System.Xml;

public class CsPhysics : ModuleRules
{
    public CsPhysics(ReadOnlyTargetRules Target) : base(Target)
    {
        // Get any Custom Settings
        string SettingsDirectory = "C:\\Trees\\core\\";
        string SettingsFile = "PluginBuildSettings.xml";
        string SettingsPath = SettingsDirectory + SettingsFile;

        XmlDocument SettingsXml = new XmlDocument();
        SettingsXml.Load(SettingsPath);
        XmlNode bUseUnityNode = SettingsXml.SelectSingleNode("/Settings/bUseUnity");

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;
        bUseUnity = bUseUnityNode != null ? bool.Parse(bUseUnityNode.InnerText) : true;

        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "DeveloperSettings",
                    "CsMacro",
                    "CsEnum",
                    "CsValid",
                    "CsContainer",
                    "CsTypes",
                    "CsCoreLibrary",
                    "CsCore"
,                }
            );

       PrivateDependencyModuleNames.AddRange(
                new string[] {
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
                }
            );
        }
    }
}