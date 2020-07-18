// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_StatusEffect.h"
#include "CsSe.h"

// StatusEffectTriggerCondition
#pragma region

namespace NCsStatusEffectTriggerCondition
{
	namespace Ref
	{
		CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsStatusEffectTriggerCondition, OnParentTrigger, "On Parent Trigger");
		CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsStatusEffectTriggerCondition, OnHit, "On Hit");
	}
}

#pragma endregion StatusEffectTriggerCondition

// StatusEffectTriggerType
#pragma region

namespace NCsStatusEffectTriggerType
{
	namespace Ref
	{
		CSSE_API CS_ADD_TO_ENUM_MAP(EMCsStatusEffectTriggerType, Once);
		CSSE_API CS_ADD_TO_ENUM_MAP(EMCsStatusEffectTriggerType, Count);
		CSSE_API CS_ADD_TO_ENUM_MAP(EMCsStatusEffectTriggerType, Infinite);
		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsStatusEffectTriggerType, ECsStatusEffectTriggerType_MAX, "MAX");
	}

	CSSE_API const uint8 MAX = (uint8)Type::ECsStatusEffectTriggerType_MAX;
}

#pragma endregion StatusEffectTriggerType