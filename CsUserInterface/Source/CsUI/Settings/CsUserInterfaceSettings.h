// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings.h"
#include "Settings/CsTypes_UserInterfaceSettings.h"
#include "Managers/WidgetActor/CsSettings_Manager_WidgetActor.h"
#include "CsUserInterfaceSettings.generated.h"

// Cached
#pragma region

#pragma endregion Cached

class UDataTable;

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs User Interface Settings"))
class CSUI_API UCsUserInterfaceSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:

// Enum
#pragma region
public:

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<typename EnumType>
	FString GetSettingsEnumPath() const;

	// WidgetActor

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWidgetActor - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsWidgetActor_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWidgetActor"))
	TArray<FCsSettings_Enum> ECsWidgetActor;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsWidgetActor>() const
	{
		return ECsWidgetActor;
	}

	template<>
	FString GetSettingsEnumPath<FECsWidgetActor>() const
	{
		return TEXT("UCsUserInterfaceSettings.ECsWidgetActor");
	}

	// WidgetActorClass

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWidgetActorClass - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsProjectileClass_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWidgetActorClass"))
	TArray<FCsSettings_Enum> ECsWidgetActorClass;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsWidgetActorClass>() const
	{
		return ECsWidgetActorClass;
	}

	template<>
	FString GetSettingsEnumPath<FECsWidgetActorClass>() const
	{
		return TEXT("UCsUserInterfaceSettings.ECsWidgetActorClass");
	}

#pragma endregion Enum

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_WidgetActor Manager_WidgetActor;

// Unit Test
#pragma region
public:

	//UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Unit Test", meta = (DisplayName = "Unit Test Plan: Manager Creep"))
	//FCsTdSettings_UnitTestPlan_Manager_Creep UnitTestPlan_ManagerCreep;

#pragma endregion Unit Test
};