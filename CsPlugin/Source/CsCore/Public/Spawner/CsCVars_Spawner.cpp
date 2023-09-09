// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Spawner/CsCVars_Spawner.h"

TAutoConsoleVariable<int32> CsCVarLogSpawnerTransactions(
	TEXT("log.spawner.transactions"),
	0,
	TEXT("Log Spawner Transactions."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSpawnerTransactions, "Log Spawner Transactions");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSpawnerTransactions, CsCVarLogSpawnerTransactions);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	namespace Map
	{
	}
}

#pragma endregion ScopedGroup