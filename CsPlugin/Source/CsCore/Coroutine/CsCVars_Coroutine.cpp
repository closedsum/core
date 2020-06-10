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
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogRoutineScopedTimer, "Log Routine Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogCoroutineScopedTimer, "Log Coroutine Scoped Timer");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogCoroutineTransactions, CsCVarLogCoroutineTransactions);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogCoroutineRunning, CsCVarLogCoroutineRunning);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogRoutineScopedTimer, CsCVarLogRoutineScopedTimer);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogCoroutineScopedTimer, CsCVarLogCoroutineScopedTimer);
	}
}

#pragma endregion CVarLog