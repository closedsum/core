// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsPayload_Sound.h"

// DeallocateMethod
#pragma region

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

#pragma endregion DeallocateMethod

const FName NCsSound::NPayload::IPayload::Name = FName("NCsSound::NPayload::IPayload");