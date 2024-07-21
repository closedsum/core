// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Performance/CsCVars_Manager_Performance.h"

TAutoConsoleVariable<int32> CsCVarLogManagerPerformance(
	TEXT("log.manager.performance"),
	0,
	TEXT("Log Manager Performance.\n")
	TEXT("\n")
	TEXT("Log Manager Performance actions.\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSPERFORMANCE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerPerformance, "Log Manager Performance");

	namespace Map
	{
		CSPERFORMANCE_API CS_ADD_TO_CVAR_MAP(LogManagerPerformance, CsCVarLogManagerPerformance);
	}
}

#pragma endregion CVarLog