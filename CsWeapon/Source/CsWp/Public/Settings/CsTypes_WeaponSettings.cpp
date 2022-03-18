// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsTypes_WeaponSettings.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsWeaponSettings.h"

// FCsWeaponSettings_ProjectileWeaponImpl
#pragma region

bool FCsWeaponSettings_ProjectileWeaponImpl::IsValidChecked(const FString& Context) const
{
	// Check IdleState is Valid.
	CS_IS_ENUM_STRUCT_SET_VALID_CHECKED(EMCsWeaponState, IdleState);
	// Check FireState is Valid.
	CS_IS_ENUM_STRUCT_SET_VALID_CHECKED(EMCsWeaponState, FireState);
	return true;
}

const FCsWeaponSettings_ProjectileWeaponImpl& FCsWeaponSettings_ProjectileWeaponImpl::Get()
{
	return GetMutableDefault<UCsWeaponSettings>();
}

#pragma endregion FCsWeaponSettings_ProjectileWeaponImpl