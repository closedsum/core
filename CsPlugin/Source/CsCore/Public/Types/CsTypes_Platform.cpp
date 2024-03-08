// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Platform.h"

// Platform
#pragma region

namespace NCsPlatform
{
	namespace Ref
	{
		typedef EMCsPlatform EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Windows);
		CSCORE_API CS_ADD_TO_ENUM_MAP(IOS);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Android);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Xbox);
		CSCORE_API CS_ADD_TO_ENUM_MAP(PlayStation);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPlatform_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)ECsPlatform::ECsPlatform_MAX;
}

#pragma endregion Platform