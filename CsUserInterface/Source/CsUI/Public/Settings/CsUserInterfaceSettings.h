// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
#include "Settings/CsTypes_UserInterfaceSettings.h"
#include "Managers/WidgetActor/CsSettings_Manager_WidgetActor.h"
#include "Managers/UserWidget/CsSettings_Manager_UserWidget.h"

#include "CsUserInterfaceSettings.generated.h"

// Cached
#pragma region

namespace NCsUserInterfaceSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSUI_API const FString WidgetActor;
			extern CSUI_API const FString UserWidget;
			extern CSUI_API const FString UserWidgetPooled;
		}
	}
}

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
	const FString& GetSettingsEnumPath() const;

#pragma endregion Enum

// WidgetActor
#pragma region
public:

	// WidgetActor

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|WidgetActor", meta = (DisplayName = "ECsWidgetActor - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsWidgetActor_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|WidgetActor", meta = (DisplayName = "ECsWidgetActor"))
	TArray<FCsSettings_Enum> ECsWidgetActor;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsWidgetActor>() const
	{
		return ECsWidgetActor;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsWidgetActor>() const
	{
		return NCsUserInterfaceSettings::NCached::Str::WidgetActor;
	}

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|WidgetActor")
	FCsSettings_Manager_WidgetActor Manager_WidgetActor;

	// Unit Test
#pragma region
public:

	//UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|WidgetActor|Unit Test", meta = (DisplayName = "Unit Test Plan: Manager WidgetActor"))
	//FCsSettings_UnitTestPlan_Manager_WidgetActor UnitTestPlan_ManagerWidgetActor;

#pragma endregion Unit Test

#pragma endregion WidgetActor

// UserWidget
#pragma region
public:

	// UserWidget

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget", meta = (DisplayName = "ECsUserWidget - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsUserWidget_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget", meta = (DisplayName = "ECsUserWidget"))
	TArray<FCsSettings_Enum> ECsUserWidget;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsUserWidget>() const
	{
		return ECsUserWidget;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsUserWidget>() const
	{
		return NCsUserInterfaceSettings::NCached::Str::UserWidget;
	}

	// UserWidgetPooled

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget", meta = (DisplayName = "ECsUserWidgetPooled - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsUserWidgetPooled_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget", meta = (DisplayName = "ECsUserWidgetPooled"))
	TArray<FCsSettings_Enum> ECsUserWidgetPooled;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsUserWidgetPooled>() const
	{
		return ECsUserWidgetPooled;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsUserWidgetPooled>() const
	{
		return NCsUserInterfaceSettings::NCached::Str::UserWidgetPooled;
	}

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget")
	bool bManagerUserWidgetFromLevel;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget")
	FCsSettings_Manager_UserWidget Manager_UserWidget;

#pragma endregion UserWidget
};