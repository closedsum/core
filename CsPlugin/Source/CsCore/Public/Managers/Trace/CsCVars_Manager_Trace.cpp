// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsCVars_Manager_Trace.h"

TAutoConsoleVariable<int32> CsCVarLogManagerTraceTransactions(
	TEXT("log.manager.trace.transactions"),
	0,
	TEXT("Log Manager Trace Add and Complete."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawManagerTraceRequests(
	TEXT("draw.manager.trace.requests"),
	0,
	TEXT("Draw Manager Trace Requests. A Line from Start to End of the Trace Request"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawManagerTraceResponses(
	TEXT("draw.manager.trace.responses"),
	0,
	TEXT("Draw Manager Trace Responses. A Line from Start to End of the Trace Result / Response."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogManagerTraceTransactions);

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerTraceTransactions, CsCVarLogManagerTraceTransactions);
	}
}

#pragma endregion CVarLog

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(DrawManagerTraceRequests);
	CSCORE_API CS_CREATE_ENUM_STRUCT(DrawManagerTraceResponses);

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(DrawManagerTraceRequests, CsCVarDrawManagerTraceRequests);
		CSCORE_API CS_ADD_TO_CVAR_MAP(DrawManagerTraceResponses, CsCVarDrawManagerTraceResponses);
	}
}

#pragma endregion CVarDraw