// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Params/CsParams_FX.h"

namespace NCsFX
{
	namespace NParameter
	{
		namespace NValue
		{
			namespace Ref
			{
				typedef EMValue EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MAP(Int);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Float);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Vector);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EValue_MAX, "MAX");
			}

			CSCORE_API const uint8 MAX = (uint8)Type::EValue_MAX;
		}
	}
}