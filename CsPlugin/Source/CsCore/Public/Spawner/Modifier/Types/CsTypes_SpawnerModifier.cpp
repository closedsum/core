// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Spawner/Modifier/Types/CsTypes_SpawnerModifier.h"

// SpawnerModifier
#pragma region

namespace NCsSpawnerModifier
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(MovementSpeed, "Movement Speed");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(SteeringSeparateForcePriority, "Steering Separate Force Priority");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(SteeringSeparateForceRadius, "Steering Separate Force Radius");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(CollisionRadius, "Collision Radius");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(KnockbackEnabled, "Knockback Enabled");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(AttackSpeed, "Attack Speed");
}

#pragma endregion SpawnerModifier

// SpawnerModifier_Int
#pragma region

namespace NCsSpawnerModifier_Int
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(SteeringSeparateForcePriority, "Steering Separate Force Priority");
}

#pragma endregion SpawnerModifier_Int

// SpawnerModifier_Float
#pragma region

namespace NCsSpawnerModifier_Float
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(MovementSpeed, "Movement Speed");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(SteeringSeparateForceRadius, "Steering Separate Force Radius");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(CollisionRadius, "Collision Radius");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(AttackSpeed, "Attack Speed");
}

#pragma endregion SpawnerModifier_Float

// SpawnerModifier_Toggle
#pragma region

namespace NCsSpawnerModifier_Toggle
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(KnockbackEnabled, "Knockback Enabled");
}

#pragma endregion SpawnerModifier_Toggle