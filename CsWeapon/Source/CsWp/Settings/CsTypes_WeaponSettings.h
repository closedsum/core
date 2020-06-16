// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Weapon.h"
#include "CsTypes_WeaponSettings.generated.h"
#pragma once

// FCsWeaponSettings_WeaponsRowName
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_WeaponsRowName
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	FCsWeaponSettings_WeaponsRowName() :
		Name(NAME_None)
	{
	}
};

#pragma endregion FCsWeaponSettings_WeaponsRowName

// FCsWeaponSettings_DataTable_Weapon
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_DataTable_Weapons
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FECsWeaponData> EmulatedDataInterfaces;

	FCsWeaponSettings_DataTable_Weapons() :
		Weapons(nullptr),
		EmulatedDataInterfaces()
	{
	}
};

#pragma endregion FCsWeaponSettings_DataTable_Weapon