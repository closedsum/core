// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
// FX
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/FX/Actor/CsSettings_Manager_FX.h"

#include "CsFXSettings.generated.h"

// Cached
#pragma region

namespace NCsFXSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSFX_API const FString FX;
		}
	}
}

#pragma endregion Cached

class UDataTable;

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsFX Settings"))
class CSFX_API UCsFXSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<typename EnumType>
	const FString& GetSettingsEnumPath() const;

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
	const FString& GetSettingsEnumPath<FECsFX>() const { return NCsFXSettings::NCached::Str::FX; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "Default Value: ECsStaticMeshActor"))
	FECsFX Default_ECsFX;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX")
	TArray<TSoftObjectPtr<UDataTable>> FXs;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|FX", meta = (DisplayName = "Manager FX"))
	FCsSettings_Manager_FX Manager_FX;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion FX

};