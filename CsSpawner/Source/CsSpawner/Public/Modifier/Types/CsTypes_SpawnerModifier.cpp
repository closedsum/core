// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Modifier/Types/CsTypes_SpawnerModifier.h"

// SpawnerModifier
#pragma region

namespace NCsSpawnerModifier
{
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(MovementSpeed, "Movement Speed");
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(SteeringSeparateForcePriority, "Steering Separate Force Priority");
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(SteeringSeparateForceRadius, "Steering Separate Force Radius");
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(CollisionRadius, "Collision Radius");
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(KnockbackEnabled, "Knockback Enabled");
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(AttackSpeed, "Attack Speed");
}

#pragma endregion SpawnerModifier

// SpawnerModifier_Int
#pragma region

namespace NCsSpawnerModifier_Int
{
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(SteeringSeparateForcePriority, "Steering Separate Force Priority");
}

#pragma endregion SpawnerModifier_Int

// SpawnerModifier_Float
#pragma region

namespace NCsSpawnerModifier_Float
{
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(MovementSpeed, "Movement Speed");
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(SteeringSeparateForceRadius, "Steering Separate Force Radius");
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(CollisionRadius, "Collision Radius");
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(AttackSpeed, "Attack Speed");
}

#pragma endregion SpawnerModifier_Float

// SpawnerModifier_Toggle
#pragma region

namespace NCsSpawnerModifier_Toggle
{
	CSSPAWNER_API CS_CREATE_ENUM_STRUCT_CUSTOM(KnockbackEnabled, "Knockback Enabled");
}

#pragma endregion SpawnerModifier_Toggle