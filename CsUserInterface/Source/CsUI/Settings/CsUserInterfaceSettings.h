// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings.h"
#include "Settings/CsTypes_UserInterfaceSettings.h"
#include "Managers/WidgetActor/CsSettings_Manager_WidgetActor.h"
#include "Managers/UserWidget/CsSettings_Manager_UserWidget.h"

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
	FString GetSettingsEnumPath<FECsWidgetActor>() const
	{
		return TEXT("UCsUserInterfaceSettings.ECsWidgetActor");
	}

	// WidgetActorClass

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|WidgetActor", meta = (DisplayName = "ECsWidgetActorClass - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsWidgetActorClass_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|WidgetActor", meta = (DisplayName = "ECsWidgetActorClass"))
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
	FString GetSettingsEnumPath<FECsUserWidget>() const
	{
		return TEXT("UCsUserInterfaceSettings.ECsUserWidget");
	}

	// UserWidgetClass

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget", meta = (DisplayName = "ECsUserWidgetClass - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsUserWidgetClass_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget", meta = (DisplayName = "ECsUserWidgetClass"))
	TArray<FCsSettings_Enum> ECsUserWidgetClass;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsUserWidgetClass>() const
	{
		return ECsUserWidgetClass;
	}

	template<>
	FString GetSettingsEnumPath<FECsUserWidgetClass>() const
	{
		return TEXT("UCsUserInterfaceSettings.ECsUserWidgetClass");
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
	FString GetSettingsEnumPath<FECsUserWidgetPooled>() const
	{
		return TEXT("UCsUserInterfaceSettings.ECsUserWidgetPooled");
	}

	// UserWidgetPooledClass

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget", meta = (DisplayName = "ECsUserWidgetPooledClass - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsUserWidgetPooledClass_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget", meta = (DisplayName = "ECsUserWidgetPooledClass"))
	TArray<FCsSettings_Enum> ECsUserWidgetPooledClass;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsUserWidgetPooledClass>() const
	{
		return ECsUserWidgetPooledClass;
	}

	template<>
	FString GetSettingsEnumPath<FECsUserWidgetPooledClass>() const
	{
		return TEXT("UCsUserInterfaceSettings.ECsUserWidgetPooledClass");
	}

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|UserWidget")
	FCsSettings_Manager_UserWidget Manager_UserWidget;

#pragma endregion UserWidget
};