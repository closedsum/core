// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Weapon/CsSettings_Manager_Weapon.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsWeaponSettings.h"

// FCsSettings_Manager_Weapon_PoolParams
#pragma region

bool FCsSettings_Manager_Weapon_PoolParams::IsValidChecked(const FString& Context) const
{
	// Check Class is Valid
	check(EMCsWeaponClass::Get().IsValidEnumChecked(Context, Class))
	// Check PoolSize is >= 4
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 4)
	// Check PayloadSize is >= 4
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PayloadSize, 4)
	return true;
}

bool FCsSettings_Manager_Weapon_PoolParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	// Check Class is Valid
	CS_IS_ENUM_STRUCT_VALID(EMCsWeaponClass, FECsWeaponClass, Class)
	// Check PoolSize is >= 4
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PoolSize, 4)
	// Check PayloadSize is >= 4
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PayloadSize, 4)
	return true;
}

#pragma endregion FCsSettings_Manager_Weapon_PoolParams

// FCsSettings_Manager_Weapon_Modifiers
#pragma region

const FCsSettings_Manager_Weapon_Modifiers& FCsSettings_Manager_Weapon_Modifiers::Get()
{
	return FCsSettings_Manager_Weapon::Get().Modifiers;
}

bool FCsSettings_Manager_Weapon_Modifiers::IsValidChecked(const FString& Context) const
{
	// Check PoolSize is >= 64
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 64)
	return true;
}

bool FCsSettings_Manager_Weapon_Modifiers::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	// Check PoolSize is >= 64
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PoolSize, 64)
	return true;
}

#pragma endregion FCsSettings_Manager_Weapon_Modifiers

// FCsSettings_Manager_Weapon_Spread
#pragma region

const FCsSettings_Manager_Weapon_Spread& FCsSettings_Manager_Weapon_Spread::Get()
{
	return FCsSettings_Manager_Weapon::Get().Spread;
}

bool FCsSettings_Manager_Weapon_Spread::IsValidChecked(const FString& Context) const
{
	// Check PoolSize is >= 64
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 64)
	return true;
}

bool FCsSettings_Manager_Weapon_Spread::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	// Check PoolSize is >= 64
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PoolSize, 64)
	return true;
}

#pragma endregion FCsSettings_Manager_Weapon_Spread

// FCsSettings_Manager_Weapon
#pragma region

const FCsSettings_Manager_Weapon& FCsSettings_Manager_Weapon::Get()
{
	return GetMutableDefault<UCsWeaponSettings>()->Manager_Weapon;
}

bool FCsSettings_Manager_Weapon::IsValidChecked(const FString& Context) const
{
	for (const TPair<FECsWeapon, FECsWeapon>& Pair : TypeMap)
	{
		CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeapon, Pair.Key)
		CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeapon, Pair.Value)
	}
	for (const TPair<FECsWeapon, FCsSettings_Manager_Weapon_PoolParams>& Pair : PoolParams)
	{
		CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeapon, Pair.Key)
		CS_IS_VALID_CHECKED(Pair.Value);
	}
	CS_IS_VALID_CHECKED(Modifiers);
	CS_IS_VALID_CHECKED(Spread);
	return true;
}

bool FCsSettings_Manager_Weapon::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	for (const TPair<FECsWeapon, FECsWeapon>& Pair : TypeMap)
	{
		CS_IS_ENUM_STRUCT_VALID(EMCsWeapon, FECsWeapon, Pair.Key)
		CS_IS_ENUM_STRUCT_VALID(EMCsWeapon, FECsWeapon, Pair.Value)
	}
	for (const TPair<FECsWeapon, FCsSettings_Manager_Weapon_PoolParams>& Pair : PoolParams)
	{
		CS_IS_ENUM_STRUCT_VALID(EMCsWeapon, FECsWeapon, Pair.Key)
		CS_IS_VALID(Pair.Value)
	}
	CS_IS_VALID(Modifiers)
	CS_IS_VALID(Spread)
	return true;
}

#pragma endregion FCsSettings_Manager_Weapon