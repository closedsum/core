// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Payload_Projectile.generated.h"
#pragma once

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
	extern CSPRJ_API const Type ProjectileDamageModifier;
}

#pragma endregion ProjectilePayload