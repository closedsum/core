// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsProjectileSettings.h"

// FCsSettings_Manager_Projectile_PoolParams
#pragma region

bool FCsSettings_Manager_Projectile_PoolParams::IsValidChecked(const FString& Context) const
{
	// Check Class is Valid
	check(EMCsProjectileClass::Get().IsValidEnumChecked(Context, Class))
	// Check PoolSize is >= 4
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 4)
	// Check PayloadSize is >= 4
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PayloadSize, 4)
	return true;
}

bool FCsSettings_Manager_Projectile_PoolParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	// Check Class is Valid
	CS_IS_ENUM_STRUCT_VALID(EMCsProjectileClass, FECsProjectileClass, Class)
	// Check PoolSize is >= 4
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PoolSize, 4)
	// Check PayloadSize is >= 4
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PayloadSize, 4)
	return true;
}

#pragma endregion FCsSettings_Manager_Projectile_PoolParams

// FCsSettings_Manager_Projectile
#pragma region

const FCsSettings_Manager_Projectile& FCsSettings_Manager_Projectile::Get()
{
	return GetMutableDefault<UCsProjectileSettings>()->Manager_Projectile;
}

#pragma endregion FCsSettings_Manager_Projectile