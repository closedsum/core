// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsAnimPlayScale.h"

namespace NCsAnimPlayScale
{
	namespace Ref
	{
		typedef EMCsAnimPlayScale EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Default);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(TotalTime, "Total Time");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAnimPlayScale_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsAnimPlayScale_MAX;
}

namespace NCsAnim
{
	namespace NPlayScale
	{
		namespace Ref
		{
			typedef EMPlayScale EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(Default);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(TotalTime, "Total Time");
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPlayScale_MAX, "MAX");
		}

		CSTYPES_API const uint8 MAX = (uint8)Type::EPlayScale_MAX;
	}
}