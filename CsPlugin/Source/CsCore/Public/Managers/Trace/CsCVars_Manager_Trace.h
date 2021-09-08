// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceTransactions;
// Scoped Timers
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerTrace;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerUpdate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerProcessAsyncRequest;
 
// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerTraceTransactions;
	// Scoped Timers
	extern CSCORE_API const Type LogManagerTraceScopedTimer;
	extern CSCORE_API const Type LogManagerTraceScopedTimerTrace;
	extern CSCORE_API const Type LogManagerTraceScopedTimerUpdate;
	extern CSCORE_API const Type LogManagerTraceScopedTimerProcessAsyncRequest;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceTransactions);
		// Scoped Timers
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerTrace);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerUpdate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerProcessAsyncRequest);
	}
}

#pragma endregion CVarLog

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerTraceRequests;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerTraceResponses;

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	extern CSCORE_API const Type DrawManagerTraceRequests;
	extern CSCORE_API const Type DrawManagerTraceResponses;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawManagerTraceRequests);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawManagerTraceResponses);
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerTrace;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerTrace);
	}
}

#pragma endregion ScopedGroup