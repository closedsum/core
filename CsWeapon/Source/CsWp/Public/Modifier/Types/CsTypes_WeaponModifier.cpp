// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
	// Point Sequence Weapons
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointSeqWp_TimeBetweenShots, "Point Sequence: Time Between Shots");
		// Sequence
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointSeqWp_Sequence_Count, "Sequence: Count");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointSeqWp_Sequence_Interval, "Sequence: Interval");
		// Points Per Shot
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointSeqWp_SequencesPerShot_Count, "Sequences per Shot: Count");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(PointSeqWp_SequencesPerShot_Interval, "Sequences per Shot: Interval");
}

#pragma endregion WeaponModifier