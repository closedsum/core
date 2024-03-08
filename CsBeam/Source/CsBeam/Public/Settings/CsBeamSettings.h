// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
#include "Managers/Beam/CsSettings_Manager_Beam.h"

#include "CsBeamSettings.generated.h"

// Cached
#pragma region

namespace NCsBeamSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSBEAM_API const FString Beam;
			extern CSBEAM_API const FString BeamClass;
		}
	}
}

#pragma endregion Cached

class UDataTable;

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Beam Settings"))
class CSBEAM_API UCsBeamSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

// Enum
#pragma region
public:

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<typename EnumType>
	const FString& GetSettingsEnumPath() const;

	// Beam

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsBeam - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsBeam_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsBeam"))
	TArray<FCsSettings_Enum> ECsBeam;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsBeam>() const
	{
		return ECsBeam;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsBeam>() const
	{
		return NCsBeamSettings::NCached::Str::Beam;
	}

	// BeamClass

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsBeamClass - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsBeamClass_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsBeamClass"))
	TArray<FCsSettings_Enum> ECsBeamClass;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsBeamClass>() const
	{
		return ECsBeamClass;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsBeamClass>() const
	{
		return NCsBeamSettings::NCached::Str::BeamClass;
	}

#pragma endregion Enum

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Beam Manager_Beam;
};