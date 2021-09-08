// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings.h"
#include "Settings/CsTypes_ProjectileSettings.h"
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"
#include "CsProjectileSettings.generated.h"

// Cached
#pragma region

namespace NCsProjectileSettings
{
	namespace Str
	{
		extern CSPRJ_API const FString Projectile;
		extern CSPRJ_API const FString ProjectileClass;
	}
}

#pragma endregion Cached

class UDataTable;

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Cs Projectile Settings"))
class CSPRJ_API UCsProjectileSettings : public UDeveloperSettings
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

	// Projectile

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsProjectile - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsProjectile_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsProjectile"))
	TArray<FCsSettings_Enum> ECsProjectile;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsProjectile>() const
	{
		return ECsProjectile;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsProjectile>() const
	{
		return NCsProjectileSettings::Str::Projectile;
	}

	// ProjectileClass

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsProjectileClass - Populate Enum Map Method"))
	ECsPopulateEnumMapMethod ECsProjectileClass_PopulateEnumMapMethod;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Enum", meta = (DisplayName = "ECsProjectileClass"))
	TArray<FCsSettings_Enum> ECsProjectileClass;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsProjectileClass>() const
	{
		return ECsProjectileClass;
	}

	template<>
	const FString& GetSettingsEnumPath<FECsProjectileClass>() const
	{
		return NCsProjectileSettings::Str::ProjectileClass;
	}

#pragma endregion Enum

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Projectile Manager_Projectile;

// Unit Test
#pragma region
public:

	//UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Unit Test", meta = (DisplayName = "Unit Test Plan: Manager Creep"))
	//FCsTdSettings_UnitTestPlan_Manager_Creep UnitTestPlan_ManagerCreep;

#pragma endregion Unit Test
};