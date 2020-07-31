// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Types/Enum/CsUserDefinedEnum.h"
#include "Settings/CsTypes_Settings.h"
// Load
#include "Managers/Load/CsSettings_Manager_Load.h"
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

#include "CsDeveloperSettings.generated.h"

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
	FString GetSettingsEnumPath() const;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum")
	FCsUserDefinedEnum InputAction;

#pragma endregion Enum

// Load
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Load", meta = (MustImplement = "CsDataRootSet"))
	TSoftClassPtr<UObject> DataRootSet;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Load", meta = (DisplayName = "Manager Load"))
	FCsSettings_Manager_Load Manager_Load;

#pragma endregion Load

// Input
#pragma region
public:

	// InputActionMap

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsInputActionMap"))
	TArray<FCsSettings_Enum> ECsInputActionMap;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsInputActionMap>() const
	{
		return ECsInputActionMap;
	}

	template<>
	FString GetSettingsEnumPath<FECsInputActionMap>() const
	{
		return TEXT("UCsDeveloperSettings.ECsInputActionMap");
	}

	// Game Event

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent"))
	TArray<FCsSettings_Enum> ECsGameEvent;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsGameEvent>() const
	{
		return ECsGameEvent;
	}

	template<>
	FString GetSettingsEnumPath<FECsGameEvent>() const
	{
		return TEXT("UCsDeveloperSettings.ECsGameEvent");
	}

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

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX", meta = (DisplayName = "ECsFX"))
	TArray<FCsSettings_Enum> ECsFX;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsFX>() const
	{
		return ECsFX;
	}

	template<>
	FString GetSettingsEnumPath<FECsFX>() const
	{
		return TEXT("UCsDeveloperSettings.ECsFX");
	}

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX")
	TArray<TSoftObjectPtr<UDataTable>> FXs;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX", meta = (DisplayName = "Manager FX Actor"))
	FCsSettings_Manager_FX_Actor Manager_FX_Actor;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion FX

// Sound
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", meta = (DisplayName = "ECsSound - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsSound_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", meta = (DisplayName = "ECsSound"))
	TArray<FCsSettings_Enum> ECsSound;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsSound>() const
	{
		return ECsSound;
	}

	template<>
	FString GetSettingsEnumPath<FECsSound>() const
	{
		return TEXT("UCsDeveloperSettings.ECsSound");
	}

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
};