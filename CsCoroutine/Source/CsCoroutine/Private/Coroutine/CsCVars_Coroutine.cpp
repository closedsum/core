// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/CsCVars_Coroutine.h"

TAutoConsoleVariable<int32> CsCVarLogCoroutineTransactions(
	TEXT("log.coroutine.transactions"),
	0,
	TEXT("Log Coroutine Scheduler Allocation and DeAllocation."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogCoroutineRunning(
	TEXT("log.coroutine.running"),
	0,
	TEXT("Log Coroutines currently running."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogRoutineEnd(
	TEXT("log.routine.end"),
	0,
	TEXT("Log Routine End."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogCoroutinesScopedTimer(
	TEXT("log.coroutines.scopedtimer"),
	0,
	TEXT("[Non-Shipping] Log Coroutines Scoped Timer"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogRoutineScopedTimer(
	TEXT("log.routine.scopedtimer"),
	0,
	TEXT("[Non-Shipping] Log Routine Scoped Timer"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogCoroutineScopedTimer(
	TEXT("log.coroutine.scopedtimer"),
	0,
	TEXT("[Non-Shipping] Log Coroutine Scoped Timer"),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCOROUTINE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogCoroutineTransactions, "Log Coroutine Transactions");
	CSCOROUTINE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogCoroutineRunning, "Log Coroutine Running");
	CSCOROUTINE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogRoutineEnd, "Log Routine End");
	// Scoped Timer
	CSCOROUTINE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogCoroutinesScopedTimer, "Log Coroutines Scoped Timer");
	CSCOROUTINE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogRoutineScopedTimer, "Log Routine Scoped Timer");
	CSCOROUTINE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogCoroutineScopedTimer, "Log Coroutine Scoped Timer");

	namespace Map
	{
		CSCOROUTINE_API CS_ADD_TO_CVAR_MAP(LogCoroutineTransactions, CsCVarLogCoroutineTransactions);
		CSCOROUTINE_API CS_ADD_TO_CVAR_MAP(LogCoroutineRunning, CsCVarLogCoroutineRunning);
		CSCOROUTINE_API CS_ADD_TO_CVAR_MAP(LogRoutineEnd, CsCVarLogRoutineEnd);
		// Scoped Timer
		CSCOROUTINE_API CS_ADD_TO_CVAR_MAP(LogCoroutinesScopedTimer, CsCVarLogCoroutinesScopedTimer);
		CSCOROUTINE_API CS_ADD_TO_CVAR_MAP(LogRoutineScopedTimer, CsCVarLogRoutineScopedTimer);
		CSCOROUTINE_API CS_ADD_TO_CVAR_MAP(LogCoroutineScopedTimer, CsCVarLogCoroutineScopedTimer);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCOROUTINE_API CS_CREATE_ENUM_STRUCT(Coroutine);

	namespace Map
	{
		CSCOROUTINE_API CS_ADD_TO_CVAR_MAP(Coroutine, CsCVarLogCoroutinesScopedTimer);
	}
}

#pragma endregion ScopedGroup