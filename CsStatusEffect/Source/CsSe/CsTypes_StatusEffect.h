// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_StatusEffect.generated.h"
#pragma once

// StatusEffectTriggerCondition
#pragma region

USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffectTriggerCondition : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStatusEffectTriggerCondition)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffectTriggerCondition)

struct CSSE_API EMCsStatusEffectTriggerCondition : public TCsEnumStructMap<FECsStatusEffectTriggerCondition, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition, uint8)
};

namespace NCsStatusEffectTriggerCondition
{
	typedef FECsStatusEffectTriggerCondition Type;

	namespace Ref
	{
		extern CSSE_API const Type OnHit;
	}
}

#pragma endregion StatusEffectTriggerCondition