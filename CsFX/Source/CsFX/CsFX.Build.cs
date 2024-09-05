// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
using System.IO;
using UnrealBuildTool;
using System.Xml;

public class CsFX : ModuleRules
{
    public CsFX(ReadOnlyTargetRules Target) : base(Target)
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
                    "Niagara",
                    "NiagaraCore",
                    "CsMacro",
                    "CsContainer",
                    "CsEnum",
                    "CsValid",
                    "CsManager",
                    "CsScopedTimer",
                    "CsTypes",
                    "CsCoreLibrary",
                    "CsTime",
                    "CsCoroutine",
                    "CsCore"
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