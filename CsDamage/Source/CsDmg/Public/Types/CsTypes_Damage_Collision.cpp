// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Damage_Collision.h"

// DamageCollisionMethod
#pragma region

namespace NCsDamageCollisionMethod
{
	namespace Ref
	{
		typedef EMCsDamageCollisionMethod EnumMapType;

		CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsSweep, "Physics Sweep");
		CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsOverlap, "Physics Overlap");
		CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDamageCollisionMethod_MAX, "MAX");
	}
}

namespace NCsDamage
{
	namespace NCollision
	{
		namespace NMethod
		{
			namespace Ref
			{
				typedef EMMethod EnumMapType;

				CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsSweep, "Physics Sweep");
				CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(PhysicsOverlap, "Physics Overlap");
				CSDMG_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMethod_MAX, "MAX");
			}
		}
	}
}

#pragma endregion DamageCollisionMethod