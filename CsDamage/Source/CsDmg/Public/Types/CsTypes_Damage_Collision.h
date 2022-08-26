// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Damage_Collision.generated.h"

// DamageCollisionMethod
#pragma region

/**
* Describes how to check if an object should receive damage.
* The "collision" is determined by the data associated with the damage.
*  Data should implement the interface: DamageShapeType (NCsDamage::NData::NShape::IShape).
*/
UENUM(BlueprintType)
enum class ECsDamageCollisionMethod : uint8
{
	PhysicsSweep					UMETA(DisplayName = "Physics Sweep"),
	PhysicsOverlap					UMETA(DisplayName = "Physics Overlap"),
	Custom							UMETA(DisplayName = "Custom"),
	ECsDamageCollisionMethod_MAX	UMETA(Hidden),
};

struct CSDMG_API EMCsDamageCollisionMethod final : public TCsEnumMap<ECsDamageCollisionMethod>
{
	CS_ENUM_MAP_BODY(EMCsDamageCollisionMethod, ECsDamageCollisionMethod)
};

namespace NCsDamageCollisionMethod
{
	typedef ECsDamageCollisionMethod Type;

	namespace Ref
	{
		extern CSDMG_API const Type PhysicsSweep;
		extern CSDMG_API const Type PhysicsOverlap;
		extern CSDMG_API const Type Custom;
		extern CSDMG_API const Type ECsDamageCollisionMethod_MAX;
	}
}

namespace NCsDamage
{
	namespace NCollision
	{
		/**
		* Describes how to check if an object should receive damage.
		* The "collision" is determined by the data associated with the damage.
		*  Data should implement the interface: DamageShapeType (NCsDamage::NData::NShape::IShape).
		*/
		enum class EMethod : uint8
		{
			PhysicsSweep,
			PhysicsOverlap,
			Custom,
			EMethod_MAX
		};

		struct CSDMG_API EMMethod final : public TCsEnumMap<EMethod>
		{
			CS_ENUM_MAP_BODY(EMMethod, EMethod)
		};

		namespace NMethod
		{
			typedef EMethod Type;

			namespace Ref
			{
				extern CSDMG_API const Type PhysicsSweep;
				extern CSDMG_API const Type PhysicsOverlap;
				extern CSDMG_API const Type Custom;
				extern CSDMG_API const Type EMethod_MAX;
			}
		}
	}
}

#pragma endregion DamageCollisionMethod