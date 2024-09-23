// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Types/Enum/CsUserDefinedEnum.h"
#include "Settings/CsTypes_Settings.h"
#include "Settings/CsTypes_Settings_Enum.h"
#include "Types/Enum/CsEnumStructLayoutHistory.h"
#include "Data/CsTypes_DataRootSet.h"
#include "Types/CsTypes_Platform.h"
// Input
#include "Managers/Input/CsTypes_InputSystem.h"
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Input/CsSettings_Input.h"
#include "Managers/Input/Enhanced/CsSettings_Input_Enhanced.h"
#include "Managers/Input/CsSettings_Manager_Input.h"
// Level
#include "Managers/Level/CsSettings_Manager_Level.h"
// Anim
#include "Animation/Vertex/CsVertexAnimNotify.h"
// Container
#include "Containers/CsSettings_Container.h"

#include "CsDeveloperSettings.generated.h"

// Cached
#pragma region

namespace NCsDeveloperSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSCORE_API const FString InputActionMap;
			extern CSCORE_API const FString GameEvent;
			extern CSCORE_API const FString Sound;
			extern CSCORE_API const FString StaticMeshActor;
			extern CSCORE_API const FString SkeletalMeshActor;
			extern CSCORE_API const FString VertexAnimNotify;
		}
	}
}

#pragma endregion Cached

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsCore Settings"))
class CSCORE_API UCsDeveloperSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// Enum
#pragma region
public:

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<typename EnumType>
	const FString& GetSettingsEnumPath() const;

	UPROPERTY(config, VisibleAnywhere, BlueprintReadOnly, Category = "Settings|Enum")
	TMap<FName, FCsEnumStructLayoutHistory> EnumStructlayoutHistoryMap;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum")
	bool bEnumStructLayoutResolveChanges;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum")
	bool bForceEnumStructLayoutResolveChanges;

#pragma endregion Enum

// Input
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input")
	ECsInputSystem InputSystem;

	// InputActionMap

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsInputActionMap", EditCondition = "InputSystem==ECsInputSystem::Default", MultiLine = true))
	FString ECsInputActionMap;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsInputActionMap: Internal", EditCondition = "InputSystem==ECsInputSystem::Default", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsInputActionMap_Internal;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsInputActionMap>() const { return ECsInputActionMap_Internal; }
	template<>
	const FString& GetSettingsEnumPath<FECsInputActionMap>() const { return NCsDeveloperSettings::NCached::Str::InputActionMap; }

	// Game Event

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent", EditCondition = "InputSystem==ECsInputSystem::Default", MultiLine = true))
	FString ECsGameEvent;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent: Internal", EditCondition = "InputSystem==ECsInputSystem::Default", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsGameEvent_Internal;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsGameEvent>() const { return ECsGameEvent_Internal; }
	template<>
	const FString& GetSettingsEnumPath<FECsGameEvent>() const { return NCsDeveloperSettings::NCached::Str::GameEvent; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (EditCondition = "InputSystem==ECsInputSystem::Default", EditConditionHides))
	FCsSettings_Input Input;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (EditCondition = "InputSystem==ECsInputSystem::Enhanced", EditConditionHides))
	FCsSettings_Input_Enhanced EnhancedInput;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "Manager Input"))
	FCsSettings_Manager_Input Manager_Input;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion Input

// Level
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Level", meta = (DisplayName = "Manager Level"))
	FCsSettings_Manager_Level Manager_Level;

#pragma endregion Level

// Anim
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Anim", meta = (DisplayName = "ECsVertexAnimNotify - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsVertexAnimNotify_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Anim", meta = (DisplayName = "ECsVertexAnimNotify", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsVertexAnimNotify;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsVertexAnimNotify>() const { return ECsVertexAnimNotify; }
	template<>
	const FString& GetSettingsEnumPath<FECsVertexAnimNotify>() const { return NCsDeveloperSettings::NCached::Str::VertexAnimNotify; }

#pragma endregion Anim

// Entry
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Entry Entry;

#pragma endregion

// Container
#pragma region

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Container Container;

#pragma endregion Container

// Script
#pragma region
public:

	/** Whether to enable the CVar: CsCVarEnableScriptChecked or not.
		 Script Checked versions by default use the 'safe' versions for Editor unless set to true.
		 By default, this is FALSE in Editor. */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bEnableScriptChecked;

#if WITH_EDITOR
	void ApplyEnableScriptChecked();
#endif // #if WITH_EDITOR

#pragma endregion Script

// PIE
#pragma region
public:

	/** Whether to override any PIE / Standalone (Editor) settings when testing from editor. 
		If Standalone, viewport dimensions will be overridden.
		If bPIE_Mobile == true, then also swap the DataRootSet to the mobile specific one. */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|PIE")
	bool bOverridePIESettings;

	/** Whether to swap the DataRootSet to the mobile specific one. */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|PIE", meta = (ScriptName = "m_bPIE_Mobile"))
	bool bPIE_Mobile;

	/** Whether Vulkan Preview for PIE is for Mobile*/
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|PIE")
	bool bPIE_VulkanPreviewMobile;

	/** If bOverridePIESettings == true,
		any settings to apply to the PIE instance (i.e. viewport dimensions). */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|PIE")
	FCsSettings_PIE PIE;

	/** If bOverridePIESettings == true,
		any settings to apply to the "Mobile" PIE instance (i.e. viewport dimensions). */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|PIE", meta = (ScriptName = "m_PIE_Mobile"))
	FCsSettings_PIE PIE_Mobile;

	/** If bOverridePIESettings == true,
		any settings to apply to the Standalone (Editor) instance (i.e. viewport dimensions). */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|PIE")
	FCsSettings_PIE Standalone;

	/** If bOverridePIESettings == true,
		any settings to apply to the Mobile Standalone (Editor) instance (i.e. viewport dimensions). */
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|PIE")
	FCsSettings_PIE Standalone_Mobile;

#pragma endregion PIE

// Editor
#pragma region
public:

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion Editor
};