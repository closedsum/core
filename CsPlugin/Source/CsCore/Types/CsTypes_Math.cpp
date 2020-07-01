// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Math.h"

// ParametricFunctionType
#pragma region

namespace NCsParametricFunctionType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsParametricFunctionType, Linear);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsParametricFunctionType, Quadratic);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsParametricFunctionType, Sine);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsParametricFunctionType, ECsParametricFunctionType_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsParametricFunctionType_MAX;
}

#pragma endregion ParametricFunctionType