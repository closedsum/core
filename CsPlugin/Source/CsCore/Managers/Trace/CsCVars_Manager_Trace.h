// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Trace

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceTransactions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerTraceRequests;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerTraceResponses;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerTraceTransactions;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceTransactions);
	}
}

#pragma endregion CVarLog

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
}

#pragma endregion ScopedGroup