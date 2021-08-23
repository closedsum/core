// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/CsAnimPlayScale.h"

namespace NCsAnimPlayScale
{
	namespace Ref
	{
		typedef EMCsAnimPlayScale EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Default);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TotalTime, "Total Time");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAnimPlayScale_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAnimPlayScale_MAX;
}

namespace NCsAnim
{
	namespace NPlayScale
	{
		namespace Ref
		{
			typedef EMPlayScale EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Default);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(TotalTime, "Total Time");
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPlayScale_MAX, "MAX");
		}

		CSCORE_API const uint8 MAX = (uint8)Type::EPlayScale_MAX;
	}
}