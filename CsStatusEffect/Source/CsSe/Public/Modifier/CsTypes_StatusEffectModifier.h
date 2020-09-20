// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_StatusEffectModifier.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffectModifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStatusEffectModifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffectModifier)

struct CSSE_API EMCsStatusEffectModifier : public TCsEnumStructMap<FECsStatusEffectModifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffectModifier, FECsStatusEffectModifier, uint8)
};

namespace NCsStatusEffectModifier
{
	typedef FECsStatusEffectModifier Type;
	typedef EMCsStatusEffectModifier EnumMapType;

	extern CSSE_API const Type DamageValue;
	extern CSSE_API const Type DamageRange;
}