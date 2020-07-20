// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_StatusEffect.h"
#include "CsSe.h"

// StatusEffectTriggerCondition
#pragma region

namespace NCsStatusEffectTriggerCondition
{
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsStatusEffectTriggerCondition, OnParentTrigger, "On Parent Trigger");
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsStatusEffectTriggerCondition, OnHit, "On Hit");
}

#pragma endregion StatusEffectTriggerCondition

// StatusEffectTriggerFrequency
#pragma region

namespace NCsStatusEffectTriggerFrequency
{
	namespace Ref
	{
		CSSE_API CS_ADD_TO_ENUM_MAP(EMCsStatusEffectTriggerFrequency, Once);
		CSSE_API CS_ADD_TO_ENUM_MAP(EMCsStatusEffectTriggerFrequency, Count);
		CSSE_API CS_ADD_TO_ENUM_MAP(EMCsStatusEffectTriggerFrequency, Infinite);
		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsStatusEffectTriggerFrequency, ECsStatusEffectTriggerFrequency_MAX, "MAX");
	}

	CSSE_API const uint8 MAX = (uint8)Type::ECsStatusEffectTriggerFrequency_MAX;
}

#pragma endregion StatusEffectTriggerFrequency

// StatusEffectEvent
#pragma region

namespace NCsStatusEffectEvent
{
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsStatusEffectEvent, Default, "ICsStatusEffectEvent");
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsStatusEffectEvent, Damage, "ICsStatusEffectDamageEvent");
}

#pragma endregion StatusEffectEvent