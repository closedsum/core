// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Platform.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Platform)

// Platform
#pragma region

namespace NCsPlatform
{
	namespace Ref
	{
		typedef EMCsPlatform EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Windows);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(IOS);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Android);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Xbox);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(PlayStation);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPlatform_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)ECsPlatform::ECsPlatform_MAX;
}

#pragma endregion Platform