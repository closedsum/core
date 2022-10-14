// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Types/CsTypes_WeaponModifier.h"

// WeaponModifier
#pragma region

namespace NCsWeaponModifier
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_TimeBetweenShots, "Time Between Shots");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_TimeBetweenProjectilesPerShot, "Time Between Projectiles per Shot");
	// Projectile Per Shot
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_ProjectilesPerShot_Count, "Projectiles per Shot: Count");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_ProjectilesPerShot_Interval, "Projectiles per Shot: Interval");
	// Spread
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_UseSpreadParams, "Use Spread Params");

}

#pragma endregion WeaponModifier