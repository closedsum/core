// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"
#include "CsProjectileSettings.generated.h"

// Cached
#pragma region

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

#pragma endregion Enum

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TSoftObjectPtr<UDataTable> Projectiles;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FCsSettings_Manager_Projectile ManagerProjectile;

// Unit Test
#pragma region
public:

	//UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Unit Test", meta = (DisplayName = "Unit Test Plan: Manager Creep"))
	//FCsTdSettings_UnitTestPlan_Manager_Creep UnitTestPlan_ManagerCreep;

#pragma endregion Unit Test
};