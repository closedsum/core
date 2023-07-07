// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponState, IdleState);
	// Check FireState is Valid.
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponState, FireState);
	return true;
}

const FCsWeaponSettings_ProjectileWeaponImpl& FCsWeaponSettings_ProjectileWeaponImpl::Get()
{
	return GetMutableDefault<UCsWeaponSettings>()->ProjectileWeaponImpl;
}

#pragma endregion FCsWeaponSettings_ProjectileWeaponImpl

// FCsWeaponSettings_PointWeaponImpl
#pragma region

bool FCsWeaponSettings_PointWeaponImpl::IsValidChecked(const FString& Context) const
{
	// Check IdleState is Valid.
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponState, IdleState);
	// Check FireState is Valid.
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponState, FireState);
	return true;
}

const FCsWeaponSettings_PointWeaponImpl& FCsWeaponSettings_PointWeaponImpl::Get()
{
	return GetMutableDefault<UCsWeaponSettings>()->PointWeaponImpl;
}

#pragma endregion FCsWeaponSettings_PointWeaponImpl

// FCsWeaponSettings_PointSequenceWeaponImpl
#pragma region

bool FCsWeaponSettings_PointSequenceWeaponImpl::IsValidChecked(const FString& Context) const
{
	// Check IdleState is Valid.
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponState, IdleState);
	// Check FireState is Valid.
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponState, FireState);
	return true;
}

const FCsWeaponSettings_PointSequenceWeaponImpl& FCsWeaponSettings_PointSequenceWeaponImpl::Get()
{
	return GetMutableDefault<UCsWeaponSettings>()->PointSequenceWeaponImpl;
}

#pragma endregion FCsWeaponSettings_PointWeaponImpl