// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_ProjectileModifier.generated.h"

// ProjectileModifier
#pragma region

USTRUCT(BlueprintType)
struct CSPRJ_API FECsProjectileModifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsProjectileModifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsProjectileModifier)

struct CSPRJ_API EMCsProjectileModifier : public TCsEnumStructMap<FECsProjectileModifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsProjectileModifier, FECsProjectileModifier, uint8)
};

namespace NCsProjectileModifier
{
	typedef FECsProjectileModifier Type;
	typedef EMCsProjectileModifier EnumMapType;

	extern CSPRJ_API const Type LifeTime;
	extern CSPRJ_API const Type InitialSpeed;
	extern CSPRJ_API const Type MaxSpeed;
	// Collision
	extern CSPRJ_API const Type CollisionRadius;
	extern CSPRJ_API const Type HitCount;
}

#pragma endregion ProjectileModifier

// ProjectileModifierImpl
#pragma region

namespace NCsProjectile
{
	namespace NModifier
	{
		enum class EImpl : uint8
		{
			Int,
			Float,
			Toggle,
			EImpl_MAX
		};
	}
}

#pragma endregion ProjectileModifierImpl