// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings.h"
#include "Settings/CsTypes_WeaponSettings.h"
#include "Managers/Weapon/CsSettings_Manager_Weapon.h"
#include "CsWeaponSettings.generated.h"

class UDataTable;

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Weapon Settings"))
class CSWP_API UCsWeaponSettings : public UDeveloperSettings
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

	// Weapon

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWeapon - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsWeapon_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWeapon"))
	TArray<FCsSettings_Enum> ECsWeapon;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsWeapon>() const
	{
		return ECsWeapon;
	}

	template<>
	FString GetSettingsEnumPath<FECsWeapon>() const
	{
		return TEXT("UCsWeaponSettings.ECsWeapon");
	}

	// WeaponClass

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWeaponClass - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsWeaponClass_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWeaponClass"))
	TArray<FCsSettings_Enum> ECsWeaponClass;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsWeaponClass>() const
	{
		return ECsWeaponClass;
	}

	template<>
	FString GetSettingsEnumPath<FECsWeaponClass>() const
	{
		return TEXT("UCsWeaponSettings.ECsWeaponClass");
	}

#pragma endregion Enum
	
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Weapon ManagerWeapon;
	
// Unit Test
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Unit Test", meta = (DisplayName = "Unit Test: Manager Weapon"))
	FCsSettings_Manager_Weapon_UnitTest UnitTest_ManagerWeapon;

#pragma endregion Unit Test

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
};