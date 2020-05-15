// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings.h"
#include "Managers/Creep/CsTdSettings_Manager_Creep.h"
#include "CsTdSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Tower Defense Settings"))
class CSTD_API UCsTdSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

// Enum
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum")
	TArray<FCsSettings_Enum> ECsTdCreep;

#if WITH_EDITOR

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsTdCreep>() const
	{
		return ECsTdCreep;
	}

	template<typename EnumType>
	FString GetSettingsEnumPath() const;

	template<>
	FString GetSettingsEnumPath<FECsTdCreep>() const
	{
		return TEXT("UCsTdSettings.ECsTdCreep");
	}

#endif // #if WITH_EDITOR

#pragma endregion Enum

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsTdSettings_Manager_Creep ManagerCreep;
};