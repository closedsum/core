// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Payload_Projectile.generated.h"

// ProjectilePayload
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FECsProjectilePayload : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsProjectilePayload)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsProjectilePayload)

struct CSPRJ_API EMCsProjectilePayload : public TCsEnumStructMap<FECsProjectilePayload, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsProjectilePayload, FECsProjectilePayload, uint8)
};

namespace NCsProjectilePayload
{
	typedef FECsProjectilePayload Type;
	typedef EMCsProjectilePayload EnumMapType;

	extern CSPRJ_API const Type Projectile;
	extern CSPRJ_API const Type ProjectileCollision;
	extern CSPRJ_API const Type ProjectileModifier;
	extern CSPRJ_API const Type ProjectileModifierDamage;
	extern CSPRJ_API const Type ProjectileTarget;
}

#pragma endregion ProjectilePayload