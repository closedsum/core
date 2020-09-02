// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogCoroutineTransactions, "Log Coroutine Transactions");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogCoroutineRunning, "Log Coroutine Running");
	// Scoped Timer
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogCoroutinesScopedTimer, "Log Coroutines Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogRoutineScopedTimer, "Log Routine Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogCoroutineScopedTimer, "Log Coroutine Scoped Timer");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogCoroutineTransactions, CsCVarLogCoroutineTransactions);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogCoroutineRunning, CsCVarLogCoroutineRunning);
		// Scoped Timer
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogCoroutinesScopedTimer, CsCVarLogCoroutinesScopedTimer);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogRoutineScopedTimer, CsCVarLogRoutineScopedTimer);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogCoroutineScopedTimer, CsCVarLogCoroutineScopedTimer);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsScopedGroup, Coroutine);

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsScopedGroupMap, Coroutine, CsCVarLogCoroutinesScopedTimer);
	}
}

#pragma endregion ScopedGroup