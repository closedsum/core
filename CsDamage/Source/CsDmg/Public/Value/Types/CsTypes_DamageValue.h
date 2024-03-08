// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_DamageValue.generated.h"

USTRUCT(BlueprintType)
struct CSDMG_API FECsDamageValue : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDamageValue)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDamageValue)

struct CSDMG_API EMCsDamageValue : public TCsEnumStructMap<FECsDamageValue, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDamageValue, FECsDamageValue, uint8)
};

namespace NCsDamageValue
{
	typedef FECsDamageValue Type;
	typedef EMCsDamageValue EnumMapType;

	extern CSDMG_API const Type Point;
	extern CSDMG_API const Type Range;
}