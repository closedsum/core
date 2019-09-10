// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Sound.h"
#include "CsCore.h"

// SoundPriority
#pragma region

namespace ECsSoundPriority
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