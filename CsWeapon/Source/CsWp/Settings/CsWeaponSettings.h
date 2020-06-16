// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
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

	/*
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum")
	TArray<FCsSettings_Enum> ECsProjectile;

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsProjectile>() const
	{
		return ECsProjectile;
	}

	template<typename EnumType>
	FString GetSettingsEnumPath() const;

	template<>
	FString GetSettingsEnumPath<FECsProjectile>() const
	{
		return TEXT("UCsProjectileSettings.ECsProjectile");
	}
	*/

#pragma endregion Enum

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TArray<FCsWeaponSettings_DataTable_Weapons> Weapons;
	
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