// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
#include "Settings/CsTypes_WeaponSettings.h"
#include "Managers/Weapon/CsSettings_Manager_Weapon.h"
#include "CsWeaponSettings.generated.h"

// Cached
#pragma region

namespace NCsWeaponSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSWP_API const FString Weapon;
			extern CSWP_API const FString WeaponClass;
			extern CSWP_API const FString WeaponState;
		}
	}
}

#pragma endregion Cached

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
	const FString& GetSettingsEnumPath() const;

	// Weapon

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWeapon - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsWeapon_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (TitleProperty = "Name", DisplayName = "ECsWeapon"))
	TArray<FCsSettings_Enum> ECsWeapon;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsWeapon>() const
	{
		return ECsWeapon;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsWeapon>() const
	{
		return NCsWeaponSettings::NCached::Str::Weapon;
	}

	// WeaponClass

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsWeaponClass - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsWeaponClass_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (TitleProperty = "Name", DisplayName = "ECsWeaponClass"))
	TArray<FCsSettings_Enum> ECsWeaponClass;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsWeaponClass>() const
	{
		return ECsWeaponClass;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsWeaponClass>() const
	{
		return NCsWeaponSettings::NCached::Str::WeaponClass;
	}

	// WeaponState

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (TitleProperty = "Name", DisplayName = "ECsWeaponState"))
	TArray<FCsSettings_Enum> ECsWeaponState;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsWeaponState>() const
	{
		return ECsWeaponState;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsWeaponState>() const
	{
		return NCsWeaponSettings::NCached::Str::WeaponState;
	}

#pragma endregion Enum
	
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Weapon Manager_Weapon;
	
// Unit Test
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Unit Test", meta = (DisplayName = "Unit Test: Manager Weapon"))
	FCsSettings_Manager_Weapon_UnitTest UnitTest_ManagerWeapon;

#pragma endregion Unit Test

// Implementation
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Implementation")
	FCsWeaponSettings_ProjectileWeaponImpl ProjectileWeaponImpl;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Implementation")
	FCsWeaponSettings_TraceWeaponImpl TraceWeaponImpl;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Implementation")
	FCsWeaponSettings_PointWeaponImpl PointWeaponImpl;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Implementation")
	FCsWeaponSettings_PointSequenceWeaponImpl PointSequenceWeaponImpl;

#pragma endregion Implementation
};