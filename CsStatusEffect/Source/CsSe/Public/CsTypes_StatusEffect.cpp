// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_StatusEffect.h"
#include "CsSe.h"

// StatusEffectTriggerCondition
#pragma region

namespace NCsStatusEffectTriggerCondition
{
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(OnParentTrigger, "On Parent Trigger");
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(OnHit, "On Hit");
}

#pragma endregion StatusEffectTriggerCondition

// StatusEffectTriggerFrequency
#pragma region

namespace NCsStatusEffectTriggerFrequency
{
	namespace Ref
	{
		typedef EMCsStatusEffectTriggerFrequency EnumMapType;

		CSSE_API CS_ADD_TO_ENUM_MAP(Once);
		CSSE_API CS_ADD_TO_ENUM_MAP(Count);
		CSSE_API CS_ADD_TO_ENUM_MAP(Time);
		CSSE_API CS_ADD_TO_ENUM_MAP(Infinite);
		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsStatusEffectTriggerFrequency_MAX, "MAX");
	}

	CSSE_API const uint8 MAX = (uint8)Type::ECsStatusEffectTriggerFrequency_MAX;
}

#pragma endregion StatusEffectTriggerFrequency

// StatusEffectTransferFrequency
#pragma region

namespace NCsStatusEffectTransferFrequency
{
	namespace Ref
	{
		typedef EMCsStatusEffectTransferFrequency EnumMapType;

		CSSE_API CS_ADD_TO_ENUM_MAP(None);
		CSSE_API CS_ADD_TO_ENUM_MAP(Once);
		CSSE_API CS_ADD_TO_ENUM_MAP(Count);
		CSSE_API CS_ADD_TO_ENUM_MAP(Time);
		CSSE_API CS_ADD_TO_ENUM_MAP(Infinite);
		CSSE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsStatusEffectTransferFrequency_MAX, "MAX");
	}

	CSSE_API const uint8 MAX = (uint8)Type::ECsStatusEffectTransferFrequency_MAX;
}

#pragma endregion StatusEffectTransferFrequency

// StatusEffectEvent
#pragma region

namespace NCsStatusEffectEvent
{
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(Default, "ICsStatusEffectEvent");
	CSSE_API CS_CREATE_ENUM_STRUCT_CUSTOM(Damage, "ICsStatusEffectDamageEvent");
}

#pragma endregion StatusEffectEvent