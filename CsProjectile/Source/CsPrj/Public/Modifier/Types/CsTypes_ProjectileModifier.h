// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
	extern CSPRJ_API const Type DamageValuePoint;
	//extern CSPRJ_API const Type ValueRange;
}

#pragma endregion ProjectileModifier