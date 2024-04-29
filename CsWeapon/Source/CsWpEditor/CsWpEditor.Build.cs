// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.Xml;

public class CsWpEditor : ModuleRules
{
    public CsWpEditor(ReadOnlyTargetRules Target) : base(Target)
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
                    "CsSkin",
                    "CsPrj",
                    "CsWp"
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