// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Types/Enum/CsUserDefinedEnum.h"
#include "Settings/CsTypes_Settings.h"
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

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Load")
	FCsDataRootSetContainer DataRootSet;

#pragma endregion Load

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