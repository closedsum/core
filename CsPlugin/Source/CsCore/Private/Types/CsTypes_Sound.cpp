// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Sound.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Sound
#include "Sound/SoundBase.h"

// SoundPriority
#pragma region

namespace NCsSoundPriority
{
	namespace Ref
	{
		typedef EMCsSoundPriority EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VeryLow, "Very Low");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Low);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Medium);
		CSCORE_API CS_ADD_TO_ENUM_MAP(High);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(VeryHigh, "Very High");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSoundPriority_MAX, "MAX");
	}
}

#pragma endregion SoundPriority

// SoundDeallocateMethod
#pragma region

namespace NCsSoundDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsSoundDeallocateMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSoundDeallocateMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsSoundDeallocateMethod_MAX;
}

namespace NCsSound
{
	namespace NDeallocateMethod
	{
		namespace Ref
		{
			typedef EMDeallocateMethod EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(LifeTime);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDeallocateMethod_MAX, "MAX");
		}

		CSCORE_API const uint8 MAX = (uint8)Type::EDeallocateMethod_MAX;
	}
}

#pragma endregion SoundDeallocateMethod