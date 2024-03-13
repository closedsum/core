// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Trace/Data/Visual/CsTypes_Trace_Visual.h"

// TraceVisualAttach
#pragma region

namespace NCsTraceVisualAttach
{
	namespace Ref
	{
		typedef EMCsTraceVisualAttach EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(None);
		CSFX_API CS_ADD_TO_ENUM_MAP(Owner);
		CSFX_API CS_ADD_TO_ENUM_MAP(Component);
		CSFX_API CS_ADD_TO_ENUM_MAP(Custom);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceVisualAttach_MAX, "MAX");
	}

	CSFX_API const uint8 MAX = (uint8)Type::ECsTraceVisualAttach_MAX;
}

#pragma endregion TraceVisualAttach

// TraceVisualTransform
#pragma region

namespace NCsTraceVisualTransform
{
	namespace Ref
	{
		typedef EMCsTraceVisualTransform EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(None);
		CSFX_API CS_ADD_TO_ENUM_MAP(Owner);
		CSFX_API CS_ADD_TO_ENUM_MAP(Component);
		CSFX_API CS_ADD_TO_ENUM_MAP(Custom);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceVisualTransform_MAX, "MAX");
	}

	CSFX_API const uint8 MAX = (uint8)Type::ECsTraceVisualTransform_MAX;
}

#pragma endregion TraceVisualTransform