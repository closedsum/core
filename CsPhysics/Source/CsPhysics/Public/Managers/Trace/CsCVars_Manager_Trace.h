// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars_Core.h"

extern CSPHYSICS_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceTransactions;
// Scoped Timers
extern CSPHYSICS_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimer;
extern CSPHYSICS_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerTrace;
extern CSPHYSICS_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerUpdate;
extern CSPHYSICS_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceScopedTimerProcessAsyncRequest;
 
// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSPHYSICS_API const Type LogManagerTraceTransactions;
	// Scoped Timers
	extern CSPHYSICS_API const Type LogManagerTraceScopedTimer;
	extern CSPHYSICS_API const Type LogManagerTraceScopedTimerTrace;
	extern CSPHYSICS_API const Type LogManagerTraceScopedTimerUpdate;
	extern CSPHYSICS_API const Type LogManagerTraceScopedTimerProcessAsyncRequest;

	namespace Map
	{
		extern CSPHYSICS_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceTransactions);
		// Scoped Timers
		extern CSPHYSICS_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimer);
		extern CSPHYSICS_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerTrace);
		extern CSPHYSICS_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerUpdate);
		extern CSPHYSICS_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceScopedTimerProcessAsyncRequest);
	}
}

#pragma endregion CVarLog

extern CSPHYSICS_API TAutoConsoleVariable<int32> CsCVarDrawManagerTraceRequests;
extern CSPHYSICS_API TAutoConsoleVariable<int32> CsCVarDrawManagerTraceResponses;

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	extern CSPHYSICS_API const Type DrawManagerTraceRequests;
	extern CSPHYSICS_API const Type DrawManagerTraceResponses;

	namespace Map
	{
		extern CSPHYSICS_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawManagerTraceRequests);
		extern CSPHYSICS_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawManagerTraceResponses);
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSPHYSICS_API const Type ManagerTrace;

	namespace Map
	{
		extern CSPHYSICS_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerTrace);
	}
}

#pragma endregion ScopedGroup