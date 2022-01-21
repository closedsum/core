// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/Data/Visual/CsTypes_Trace_Visual.h"

// TraceVisualAttach
#pragma region

namespace NCsTraceVisualAttach
{
	namespace Ref
	{
		typedef EMCsTraceVisualAttach EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Owner);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Component);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceVisualAttach_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceVisualAttach_MAX;
}

#pragma endregion TraceVisualAttach

// TraceVisualTransform
#pragma region

namespace NCsTraceVisualTransform
{
	namespace Ref
	{
		typedef EMCsTraceVisualTransform EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Owner);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Component);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceVisualTransform_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceVisualTransform_MAX;
}

#pragma endregion TraceVisualTransform