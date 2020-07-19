// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_StatusEffect.generated.h"
#pragma once

// StatusEffectTriggerCondition
#pragma region

/**
*/
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

	extern CSSE_API const Type OnParentTrigger;
	extern CSSE_API const Type OnHit;
}

#pragma endregion StatusEffectTriggerCondition

// StatusEffectTriggerType
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsStatusEffectTriggerType : uint8
{
	Once							UMETA(DisplayName = "Once"),
	Count							UMETA(DisplayName = "Count"),
	Infinite						UMETA(DisplayName = "Infinite"),
	ECsStatusEffectTriggerType_MAX  UMETA(Hidden),
};

struct CSSE_API EMCsStatusEffectTriggerType : public TCsEnumMap<ECsStatusEffectTriggerType>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsStatusEffectTriggerType, ECsStatusEffectTriggerType)
};

namespace NCsStatusEffectTriggerType
{
	typedef ECsStatusEffectTriggerType Type;

	namespace Ref
	{
		extern CSSE_API const Type Once;
		extern CSSE_API const Type Count;
		extern CSSE_API const Type Infinite;
		extern CSSE_API const Type ECsStatusEffectTriggerType_MAX;
	}

	extern CSSE_API const uint8 MAX;
}

#pragma endregion StatusEffectTriggerType

// StatusEffectEvent
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffectEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStatusEffectEvent)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffectEvent)

struct CSSE_API EMCsStatusEffectEvent : public TCsEnumStructMap<FECsStatusEffectEvent, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffectEvent, FECsStatusEffectEvent, uint8)
};

namespace NCsStatusEffectEvent
{
	typedef FECsStatusEffectEvent Type;

	extern CSSE_API const Type Default;
	extern CSSE_API const Type Damage;
}

#pragma endregion StatusEffectEvent