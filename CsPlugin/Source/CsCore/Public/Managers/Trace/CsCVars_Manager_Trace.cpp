// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Trace/CsCVars_Manager_Trace.h"

TAutoConsoleVariable<int32> CsCVarLogManagerTraceTransactions(
	TEXT("log.manager.trace.transactions"),
	0,
	TEXT("Log Manager Trace Add and Complete."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimer(
	TEXT("log.manager.trace.scopedtimer"),
	0,
	TEXT("Log Manager Trace Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerTrace(
	TEXT("log.manager.trace.scopedtimer.trace"),
	0,
	TEXT("Log Manager Trace Scoped Timer Trace()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerUpdate(
	TEXT("log.manager.trace.scopedtimer.update"),
	0,
	TEXT("Log Manager Trace Scoped Timer Update()."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerProcessAsyncRequest(
	TEXT("log.manager.trace.scopedtimer.processasyncrequest"),
	0,
	TEXT("Log Manager Trace Scoped Timer ProcessAsyncRequest()."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogManagerTraceTransactions);
	// Scoped Timers
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerTraceScopedTimer, "Log Manager Trace Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerTraceScopedTimerTrace, "Log Manager Trace Scoped Timer Trace()");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerTraceScopedTimerUpdate, "Log Manager Trace Scoped Timer Update()");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerTraceScopedTimerProcessAsyncRequest, "Log Manager Trace Scoped Timer ProcessAsyncRequest()");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerTraceTransactions, CsCVarLogManagerTraceTransactions);
		// Scoped Timers
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimer, CsCVarLogManagerTraceScopedTimer);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerTrace, CsCVarLogManagerTraceScopedTimerTrace);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerUpdate, CsCVarLogManagerTraceScopedTimerUpdate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerProcessAsyncRequest, CsCVarLogManagerTraceScopedTimerProcessAsyncRequest);
	}
}

#pragma endregion CVarLog

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

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerTrace, "Manager Trace");

	namespace Map
	{
		extern CSCORE_API CS_ADD_TO_CVAR_MAP(ManagerTrace, CsCVarLogManagerTraceScopedTimer);
	}
}

#pragma endregion ScopedGroup