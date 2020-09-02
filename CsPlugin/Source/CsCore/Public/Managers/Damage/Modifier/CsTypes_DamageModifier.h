// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_DamageModifier.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSCORE_API FECsDamageModifier : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDamageModifier)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDamageModifier)

struct CSCORE_API EMCsDamageModifier : public TCsEnumStructMap<FECsDamageModifier, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDamageModifier, FECsDamageModifier, uint8)
};

namespace NCsDamageModifier
{
	typedef FECsDamageModifier Type;

	extern CSCORE_API const Type Value;
	extern CSCORE_API const Type Range;
}