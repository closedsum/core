// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Types/CsTypes_WeaponModifier.h"

// WeaponModifier
#pragma region

namespace NCsWeaponModifier
{
	// Projectile Weapon
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_TimeBetweenShots, "Projectile: Time Between Shots");
		// Projectiles Per Shot
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_ProjectilesPerShot_Count, "Projectiles per Shot: Count");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_ProjectilesPerShot_Interval, "Projectiles per Shot: Interval");
		// Spread
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PrjWp_UseSpreadParams, "Use Spread Params");
	// Point Weapon
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointWp_TimeBetweenShots, "Point: Time Between Shots");
		// Points Per Shot
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointWp_PointsPerShot_Count, "Points per Shot: Count");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointWp_PointsPerShot_Interval, "Points per Shot: Interval");
	// Point Sequence Weapon
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointSeqWp_TimeBetweenShots, "Point Sequence: Time Between Shots");
		// Points Per Shot
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointSeqWp_SequencesPerShot_Count, "Sequences per Shot: Count");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointSeqWp_SequencesPerShot_Interval, "Sequences per Shot: Interval");
}

#pragma endregion WeaponModifier