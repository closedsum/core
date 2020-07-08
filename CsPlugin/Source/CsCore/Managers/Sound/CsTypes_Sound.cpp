// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsTypes_Sound.h"
#include "CsCore.h"

// SoundPriority
#pragma region

namespace NCsSoundPriority
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSoundPriority, VeryLow, "Very Low");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundPriority, Low);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundPriority, Medium);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundPriority, High);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSoundPriority, VeryHigh, "Very High");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSoundPriority, ECsSoundPriority_MAX, "MAX");
	}
}

#pragma endregion SoundPriority

// SoundDeallocateMethod
#pragma region

namespace NCsSoundDeallocateMethod
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundDeallocateMethod, LifeTime);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSoundDeallocateMethod, Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSoundDeallocateMethod, ECsSoundDeallocateMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSoundDeallocateMethod_MAX;
}

#pragma endregion SoundDeallocateMethod