// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
#include "Managers/Menu/CsTypes_Menu.h"
#include "Managers/Menu/CsSettings_Manager_Menu.h"

#include "CsMenuSettings.generated.h"

// Cached
#pragma region

namespace NCsMenuSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSMENU_API const FString MenuEvent;
		}
	}
}

#pragma endregion Cached

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Menu Settings"))
class CSMENU_API UCsMenuSettings : public UDeveloperSettings
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

#pragma endregion Enum

// Menu
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Menu", meta = (DisplayName = "ECsMenuEvent - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsMenuEvent_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Menu", meta = (DisplayName = "ECsMenuEvent"))
	TArray<FCsSettings_Enum> ECsMenuEvent;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsMenuEvent>() const
	{
		return ECsMenuEvent;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsMenuEvent>() const
	{
		return NCsMenuSettings::NCached::Str::MenuEvent;
	}

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Menu")
	FCsSettings_Manager_Menu Manager_Menu;

#pragma endregion Menu
};