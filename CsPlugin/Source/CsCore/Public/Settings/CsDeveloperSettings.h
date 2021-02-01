// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Types/Enum/CsUserDefinedEnum.h"
#include "Settings/CsTypes_Settings.h"
// Data
#include "Managers/Data/CsSettings_Manager_Data.h"
// Load
#include "Managers/Load/CsSettings_Manager_Load.h"
// Runnable
#include "Managers/Runnable/CsSettings_Manager_Runnable.h"
// Input
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Input/CsSettings_Input.h"
#include "Managers/Input/CsSettings_Manager_Input.h"
// FX
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/FX/Actor/CsSettings_Manager_FX_Actor.h"
// Sound
#include "Managers/Sound/CsTypes_Sound.h"
#include "Managers/Sound/CsSettings_Manager_Sound.h"
// Trace
#include "Managers/Trace/CsSettings_Manager_Trace.h"
// Damage
#include "Managers/Damage/CsSettings_Manager_Damage.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/CsSettings_Manager_SkeletalMeshActor.h"

#include "CsDeveloperSettings.generated.h"

// Cached
#pragma region

namespace NCsDeveloperSettings
{
	namespace Str
	{
		extern CSCORE_API const FString InputActionMap;
		extern CSCORE_API const FString GameEvent;
		extern CSCORE_API const FString FX;
		extern CSCORE_API const FString Sound;
		extern CSCORE_API const FString SkeletalMeshActor;
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

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data", meta = (MustImplement = "CsDataRootSet"))
	TSoftClassPtr<UObject> DataRootSet;

	UObject* SafeLoadDataRootSet(const FString& Context);

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Data", meta = (DisplayName = "Manager Data"))
	FCsSettings_Manager_Data Manager_Data;

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
	const FString& GetSettingsEnumPath<FECsInputActionMap>() const { return NCsDeveloperSettings::Str::InputActionMap; }

	// Game Event

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent", MultiLine = true))
	FString ECsGameEvent;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent: Internal", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsGameEvent_Internal;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsGameEvent>() const { return ECsGameEvent_Internal; }
	template<>
	const FString& GetSettingsEnumPath<FECsGameEvent>() const { return NCsDeveloperSettings::Str::GameEvent; }

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
	const FString& GetSettingsEnumPath<FECsFX>() const { return NCsDeveloperSettings::Str::FX; }

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
	const FString& GetSettingsEnumPath<FECsSound>() const { return NCsDeveloperSettings::Str::Sound; }

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

// Damage
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Damage", meta = (DisplayName = "Manager Damage"))
	FCsSettings_Manager_Damage Manager_Damage;

#pragma endregion Damage

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
	const FString& GetSettingsEnumPath<FECsSkeletalMeshActor>() const { return NCsDeveloperSettings::Str::SkeletalMeshActor; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|SkeletalMeshActor", meta = (DisplayName = "Manager SkeletalMeshActor"))
	FCsSettings_Manager_SkeletalMeshActor Manager_SkeletalMeshActor;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion SkeletalMesh

// Editor
#pragma region
public:

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion Editor
};