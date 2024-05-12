// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Sound.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Sound
#include "Sound/SoundBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Sound)

// SoundPriority
#pragma region

namespace NCsSoundPriority
{
	namespace Ref
	{
		typedef EMCsSoundPriority EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VeryLow, "Very Low");
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Low);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Medium);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(High);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(VeryHigh, "Very High");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSoundPriority_MAX, "MAX");
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

		CSTYPES_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Complete);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSoundDeallocateMethod_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsSoundDeallocateMethod_MAX;
}

namespace NCsSound
{
	namespace NDeallocateMethod
	{
		namespace Ref
		{
			typedef EMDeallocateMethod EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(LifeTime);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Complete);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDeallocateMethod_MAX, "MAX");
		}

		CSTYPES_API const uint8 MAX = (uint8)Type::EDeallocateMethod_MAX;
	}
}

#pragma endregion SoundDeallocateMethod