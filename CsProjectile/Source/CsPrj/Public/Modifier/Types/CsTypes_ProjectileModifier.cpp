// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Types/CsTypes_ProjectileModifier.h"

// ProjectileModifier
#pragma region

namespace NCsProjectileModifier
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT(LifeTime);
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(InitialSpeed, "Initial Speed");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(MaxSpeed, "Max Speed");
	// Collision
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(CollisionRadius, "Collision Radius");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(HitCount, "Hit Count");
}

#pragma endregion ProjectileModifier