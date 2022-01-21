// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTypes_Trace.h"

// TraceType
#pragma region

namespace NCsTraceType
{
	namespace Ref
	{
		typedef EMCsTraceType EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Line);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sweep);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Overlap);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(OverlapBlocking, "Overlap Blocking");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceType_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceType_MAX;
}

#pragma endregion TraceType

// TraceMethod
#pragma region

namespace NCsTraceMethod
{
	namespace Ref
	{
		typedef EMCsTraceMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Test);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Single);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Multi);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceMethod_MAX;
}

#pragma endregion TraceMethod

// TraceQuery
#pragma region

namespace NCsTraceQuery
{
	namespace Ref
	{
		typedef EMCsTraceQuery EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Channel);
		CSCORE_API CS_ADD_TO_ENUM_MAP(ObjectType);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Profile);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceQuery_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceQuery_MAX;
}

#pragma endregion TraceQuery

// TraceTransaction
#pragma region

namespace NCsTraceTransaction
{
	namespace Ref
	{
		typedef EMCsTraceTransaction EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Receive);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Discard);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Add);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Process);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceTransaction_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTraceTransaction_MAX;

	namespace Str
	{
		CSCORE_API const TCsString Receive = TCsString(TEXT("Receive"), TEXT("receive"), TEXT("Receiving"));
		CSCORE_API const TCsString Discard = TCsString(TEXT("Discard"), TEXT("discard"), TEXT("Discarding"));
		CSCORE_API const TCsString Add = TCsString(TEXT("Add"), TEXT("add"), TEXT("Adding"));
		CSCORE_API const TCsString Process = TCsString(TEXT("Process"), TEXT("process"), TEXT("Processing"));
		CSCORE_API const TCsString Complete = TCsString(TEXT("Complete"), TEXT("complete"), TEXT("Completing"));
	}
}

#pragma endregion TraceTransaction