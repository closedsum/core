// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_DamageValue.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FECsDamageValue : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsDamageValue)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsDamageValue)

struct CSCORE_API EMCsDamageValue : public TCsEnumStructMap<FECsDamageValue, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsDamageValue, FECsDamageValue, uint8)
};

namespace NCsDamageValue
{
	typedef FECsDamageValue Type;
	typedef EMCsDamageValue EnumMapType;

	extern CSCORE_API const Type Point;
	extern CSCORE_API const Type Range;
}