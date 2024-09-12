// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Types/CsTypes_ProjectileModifier.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_ProjectileModifier)

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