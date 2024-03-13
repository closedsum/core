// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/CsTypes_Trace.h"

// TraceType
#pragma region

namespace NCsTraceType
{
	namespace Ref
	{
		typedef EMCsTraceType EnumMapType;

		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Line);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Sweep);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Overlap);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP_CUSTOM(OverlapBlocking, "Overlap Blocking");
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceType_MAX, "MAX");
	}

	CSPHYSICS_API const uint8 MAX = (uint8)Type::ECsTraceType_MAX;
}

#pragma endregion TraceType

// TraceMethod
#pragma region

namespace NCsTraceMethod
{
	namespace Ref
	{
		typedef EMCsTraceMethod EnumMapType;

		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Test);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Single);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Multi);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceMethod_MAX, "MAX");
	}

	CSPHYSICS_API const uint8 MAX = (uint8)Type::ECsTraceMethod_MAX;
}

#pragma endregion TraceMethod

// TraceQuery
#pragma region

namespace NCsTraceQuery
{
	namespace Ref
	{
		typedef EMCsTraceQuery EnumMapType;

		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Channel);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(ObjectType);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Profile);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceQuery_MAX, "MAX");
	}

	CSPHYSICS_API const uint8 MAX = (uint8)Type::ECsTraceQuery_MAX;
}

#pragma endregion TraceQuery

// TraceTransaction
#pragma region

namespace NCsTraceTransaction
{
	namespace Ref
	{
		typedef EMCsTraceTransaction EnumMapType;

		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Receive);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Discard);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Add);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Process);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP(Complete);
		CSPHYSICS_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceTransaction_MAX, "MAX");
	}

	CSPHYSICS_API const uint8 MAX = (uint8)Type::ECsTraceTransaction_MAX;

	namespace Str
	{
		CSPHYSICS_API const TCsString Receive = TCsString(TEXT("Receive"), TEXT("receive"), TEXT("Receiving"));
		CSPHYSICS_API const TCsString Discard = TCsString(TEXT("Discard"), TEXT("discard"), TEXT("Discarding"));
		CSPHYSICS_API const TCsString Add = TCsString(TEXT("Add"), TEXT("add"), TEXT("Adding"));
		CSPHYSICS_API const TCsString Process = TCsString(TEXT("Process"), TEXT("process"), TEXT("Processing"));
		CSPHYSICS_API const TCsString Complete = TCsString(TEXT("Complete"), TEXT("complete"), TEXT("Completing"));
	}
}

#pragma endregion TraceTransaction