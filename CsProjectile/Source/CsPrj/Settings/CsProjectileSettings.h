// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
//#include "Managers/Creep/CsTdSettings_Manager_Creep.h"
#include "CsProjectileSettings.generated.h"

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

#if WITH_EDITOR

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

#endif // #if WITH_EDITOR

#pragma endregion Enum

	//UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings")
	//FCsTdSettings_Manager_Creep ManagerCreep;

// Unit Test
#pragma region
public:

	//UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Unit Test", meta = (DisplayName = "Unit Test Plan: Manager Creep"))
	//FCsTdSettings_UnitTestPlan_Manager_Creep UnitTestPlan_ManagerCreep;

#pragma endregion Unit Test
};