// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_StatusEffect_DamageModifier.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffect_DamageModifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStatusEffect_DamageModifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffect_DamageModifier)

struct CSSE_API EMCsStatusEffect_DamageModifier : public TCsEnumStructMap<FECsStatusEffect_DamageModifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffect_DamageModifier, FECsStatusEffect_DamageModifier, uint8)
};

namespace NCsStatusEffect_DamageModifier
{
	typedef FECsStatusEffect_DamageModifier Type;

	extern CSSE_API const Type Point;
	extern CSSE_API const Type Range;
}