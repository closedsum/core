// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Weapon.h"
#include "CsWp.h"

// WeaponData
#pragma region

namespace NCsWeaponData
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsWeaponData, Weapon, "ICsData_Weapon");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsWeaponData, ProjectileWeapon, "ICsData_ProjectileWeapon");
}

#pragma endregion WeaponData