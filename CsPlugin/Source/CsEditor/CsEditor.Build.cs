// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.Xml;

public class CsEditor : ModuleRules
{
    public CsEditor(ReadOnlyTargetRules Target) : base(Target)
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
                    "SlateCore",
                    "PropertyEditor",
                    "GraphEditor",
                    "EditorStyle",
                    "LevelEditor",
                    "DeveloperToolSettings",
                    "Settings",
                    "SourceControl",
                    "Niagara", // TODO: move associated to plugin
                    "NiagaraEditor", // TODO: Move associated code to plugin
                    "CsEnum",
                    "CsEnumEditor",
                    "CsContainer",
                    "CsTypes",
                    "CsCoreLibrary",
                    "CsCore"
                }
            );
        }
        else
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "InputCore",
                    "Slate",
                    "SlateCore"
                }
            );
        }
    }
}