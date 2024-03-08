// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

// FCsSettings_Manager_Projectile_Variables
#pragma region

bool FCsSettings_Manager_Projectile_Variables::IsValidChecked(const FString& Context) const
{
	// Check PoolSize is >= 256
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 256)
	return true;
}

bool FCsSettings_Manager_Projectile_Variables::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	// Check PoolSize is >= 256
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PoolSize, 256)
	return true;
}

#pragma endregion FCsSettings_Manager_Projectile_Variables


// FCsSettings_Manager_Projectile_Modifiers
#pragma region

const FCsSettings_Manager_Projectile_Modifiers& FCsSettings_Manager_Projectile_Modifiers::Get()
{
	return GetMutableDefault<UCsProjectileSettings>()->Manager_Projectile.Modifiers;
}

#pragma endregion FCsSettings_Manager_Projectile_Modifiers

// FCsSettings_Manager_Projectile
#pragma region

const FCsSettings_Manager_Projectile& FCsSettings_Manager_Projectile::Get()
{
	return GetMutableDefault<UCsProjectileSettings>()->Manager_Projectile;
}

const FCsSettings_Manager_Projectile& FCsSettings_Manager_Projectile::GetEd()
{
	return GetMutableDefault<UCsProjectileSettings>()->Manager_Projectile;
}

bool FCsSettings_Manager_Projectile::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Variables);
	return true;
}

bool FCsSettings_Manager_Projectile::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_VALID(Variables)
	return true;
}

#pragma endregion FCsSettings_Manager_Projectile