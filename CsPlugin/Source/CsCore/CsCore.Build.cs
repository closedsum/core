// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using UnrealBuildTool;
using System.IO;
using System.Xml;

public class CsCore : ModuleRules
{
    public CsCore(ReadOnlyTargetRules Target) : base(Target)
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
                    "Niagara", // TODO: Eventually move associated to plugin
                    "CsMacro",
                    "CsContainer",
                    "CsPropertyTypes",
                    "CsEnum",
                    "CsValid",
                    "CsPIE",
                    "CsStructOps",
                    "CsManager",
                    "CsTypes",
                    "CsScopedTimer",
                    "CsCoreLibrary",
                    "CsStartPlay",
                    "CsConsoleCommand",
                    "CsTime",
                    "CsPool",
                    "CsCoroutine",
                    "CsLoad",
                    "CsData",
                    "CsInput"
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