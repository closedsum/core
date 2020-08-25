// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_StatusEffect_Modifier.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffect_Modifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStatusEffect_Modifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffect_Modifier)

struct CSSE_API EMCsStatusEffect_Modifier : public TCsEnumStructMap<FECsStatusEffect_Modifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffect_Modifier, FECsStatusEffect_Modifier, uint8)
};

namespace NCsStatusEffect_Modifier
{
	typedef FECsStatusEffect_Modifier Type;

	extern CSSE_API const Type DamageValue;
	extern CSSE_API const Type DamageRange;
}