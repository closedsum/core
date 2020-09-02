// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsTypes_Trace.h"

// TraceType
#pragma region

namespace NCsTraceType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceType, Line);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceType, Sweep);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceType, Overlap);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsTraceType, OverlapBlocking, "Overlap Blocking");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsTraceType, ECsTraceType_MAX, "MAX");
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
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceMethod, Test);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceMethod, Single);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceMethod, Multi);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsTraceMethod, ECsTraceMethod_MAX, "MAX");
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
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceQuery, Channel);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceQuery, ObjectType);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceQuery, Profile);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsTraceQuery, ECsTraceQuery_MAX, "MAX");
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
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceTransaction, Receive);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceTransaction, Discard);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceTransaction, Add);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceTransaction, Process);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsTraceTransaction, Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsTraceTransaction, ECsTraceTransaction_MAX, "MAX");
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