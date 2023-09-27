// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Types/Enum/CsUserDefinedEnum.h"
#include "Settings/CsTypes_Settings.h"
#include "Settings/CsTypes_Settings_Enum.h"
#include "Data/CsTypes_DataRootSet.h"
#include "Types/CsTypes_Platform.h"
// Data
#include "Managers/Data/CsSettings_Manager_Data.h"
// Load
#include "Managers/Load/CsSettings_Manager_Load.h"
// Runnable
#include "Managers/Runnable/CsSettings_Manager_Runnable.h"
// Time
#include "Managers/Time/CsSettings_Manager_Time.h"
// Input
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Input/CsSettings_Input.h"
#include "Managers/Input/CsSettings_Manager_Input.h"
// FX
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/FX/Actor/CsSettings_Manager_FX.h"
// Sound
#include "Managers/Sound/CsTypes_Sound.h"
#include "Managers/Sound/CsSettings_Manager_Sound.h"
// Trace
#include "Managers/Trace/CsSettings_Manager_Trace.h"
// StaticMesh
#include "Managers/StaticMesh/CsSettings_Manager_StaticMeshActor.h"
#include "Managers/StaticMesh/Instanced/CsSettings_Manager_InstancedStaticMeshComponent.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/CsSettings_Manager_SkeletalMeshActor.h"
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
			extern CSCORE_API const FString FX;
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

#pragma endregion Enum

// Data
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data", meta = (MustImplement = "/Script.CsCore.CsDataRootSet"))
	TSoftClassPtr<UObject> DataRootSet;

	UObject* LoadDataRootSetChecked(const FString& Context);
	UObject* SafeLoadDataRootSet(const FString& Context);

	UPROPERTY(config, EditAnywhere, Category = "Settings|Data")
	FCsSettings_DataRootSet DataRootSets[(uint8)ECsPlatform::ECsPlatform_MAX];

	FORCEINLINE const TSoftClassPtr<UObject>& GetDataRootSet(const ECsPlatform& Platform) const
	{
		return DataRootSets[(uint8)Platform].DataRootSet;
	}

	FORCEINLINE const FDirectoryPath& GetDirectoryToAlwaysCook(const ECsPlatform& Platform) const
	{
		return DataRootSets[(uint8)Platform].DirectoryToAlwaysCook;
	}

	UPROPERTY(config, EditAnywhere, Category = "Settings|Data")
	TArray<FString> IgnoreAssetPaths;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data", meta = (DisplayName = "Manager Data"))
	FCsSettings_Manager_Data Manager_Data;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data", meta = (DisplayName = "On Editor Startup: Load DataRootSets[Windows]"))
	bool bOnEditorStartup_LoadDataRootSet;

#if WITH_EDITOR
	void PopulateAll(const ECsPlatform& Platform);
#endif // #if WITH_EDITOR

#pragma endregion Data

// Load
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Load", meta = (DisplayName = "Manager Load"))
	FCsSettings_Manager_Load Manager_Load;

#pragma endregion Load

// Runnable
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Runnable", meta = (DisplayName = "Manager Runnable"))
	FCsSettings_Manager_Runnable Manager_Runnable;

#pragma endregion Runnable

// Time
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Time", meta = (DisplayName = "Manager Time"))
	FCsSettings_Manager_Time Manager_Time;

#pragma endregion Time

// Input
#pragma region
public:

	// InputActionMap

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsInputActionMap", MultiLine = true))
	FString ECsInputActionMap;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsInputActionMap: Internal", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsInputActionMap_Internal;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsInputActionMap>() const { return ECsInputActionMap_Internal; }
	template<>
	const FString& GetSettingsEnumPath<FECsInputActionMap>() const { return NCsDeveloperSettings::NCached::Str::InputActionMap; }

	// Game Event

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent", MultiLine = true))
	FString ECsGameEvent;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent: Internal", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsGameEvent_Internal;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsGameEvent>() const { return ECsGameEvent_Internal; }
	template<>
	const FString& GetSettingsEnumPath<FECsGameEvent>() const { return NCsDeveloperSettings::NCached::Str::GameEvent; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input")
	FCsSettings_Input Input;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "Manager Input"))
	FCsSettings_Manager_Input Manager_Input;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion Input

// FX
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX", meta = (DisplayName = "ECsFX - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsFX_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX", meta = (DisplayName = "ECsFX", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsFX;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsFX>() const { return ECsFX; }
	template<>
	const FString& GetSettingsEnumPath<FECsFX>() const { return NCsDeveloperSettings::NCached::Str::FX; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX")
	TArray<TSoftObjectPtr<UDataTable>> FXs;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX", meta = (DisplayName = "Manager FX"))
	FCsSettings_Manager_FX Manager_FX;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion FX

// Sound
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", meta = (DisplayName = "ECsSound - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsSound_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", meta = (DisplayName = "ECsSound", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsSound;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsSound>() const { return ECsSound; }
	template<>
	const FString& GetSettingsEnumPath<FECsSound>() const { return NCsDeveloperSettings::NCached::Str::Sound; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound")
	TArray<TSoftObjectPtr<UDataTable>> Sounds;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", meta = (DisplayName = "Manager Sound"))
	FCsSettings_Manager_Sound Manager_Sound;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion Sound

// Trace
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Trace", meta = (DisplayName = "Manager Trace"))
	FCsSettings_Manager_Trace Manager_Trace;

#pragma endregion Trace

// StaticMesh
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "ECsStaticMeshActor - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsStaticMeshActor_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "ECsStaticMeshActor", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsStaticMeshActor;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsStaticMeshActor>() const { return ECsStaticMeshActor; }
	template<>
	const FString& GetSettingsEnumPath<FECsStaticMeshActor>() const { return NCsDeveloperSettings::NCached::Str::StaticMeshActor; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "Default Value: ECsStaticMeshActor"))
	FECsStaticMeshActor Default_ECsStaticMeshActor;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "Manager StaticMeshActor"))
	FCsSettings_Manager_StaticMeshActor Manager_StaticMeshActor;

	// Unit Test
#pragma region

#pragma endregion Unit Test

	// Instanced
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Instanced|Component", meta = (DisplayName = "Manager InstancedStaticMeshComponent"))
	FCsSettings_Manager_InstancedStaticMeshComponent Manager_InstancedStaticMeshComponent;

#pragma endregion Instanced

#pragma endregion StaticMesh

// SkeletalMesh
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsSkeletalMeshActor_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "ECsSkeletalMeshActor", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsSkeletalMeshActor;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsSkeletalMeshActor>() const { return ECsSkeletalMeshActor; }
	template<>
	const FString& GetSettingsEnumPath<FECsSkeletalMeshActor>() const { return NCsDeveloperSettings::NCached::Str::SkeletalMeshActor; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "Default Value: ECsSkeletalMeshActor"))
	FECsSkeletalMeshActor Default_ECsSkeletalMeshActor;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "Manager SkeletalMeshActor"))
	FCsSettings_Manager_SkeletalMeshActor Manager_SkeletalMeshActor;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion SkeletalMesh

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