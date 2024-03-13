// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
// Sound
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "Managers/Sound/CsSettings_Manager_Sound.h"

#include "CsSoundSettings.generated.h"

// Cached
#pragma region

namespace NCsSoundSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSSOUND_API const FString Sound;
		}
	}
}

#pragma endregion Cached

class UDataTable;

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsSound Settings"))
class CSSOUND_API UCsSoundSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<typename EnumType>
	const FString& GetSettingsEnumPath() const;

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
	const FString& GetSettingsEnumPath<FECsSound>() const { return NCsSoundSettings::NCached::Str::Sound; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|StaticMesh|Actor", meta = (DisplayName = "Default Value: ECsStaticMeshActor"))
	FECsSound Default_ECsSound;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound")
	TArray<TSoftObjectPtr<UDataTable>> Sounds;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", meta = (DisplayName = "Manager Sound"))
	FCsSettings_Manager_Sound Manager_Sound;

	// Unit Test
#pragma region

#pragma endregion Unit Test

#pragma endregion Sound

};