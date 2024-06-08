// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/CsCVars_Manager_Level.h"

TAutoConsoleVariable<int32> CsCVarLogManagerLevelStreaming(
	TEXT("log.manager.level.streaming"),
	0,
	TEXT("Log Manager Level Streaming Events\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("Log all Level Streaming events captured by Manager Level\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogManagerLevelStreaming);

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerLevelStreaming, CsCVarLogManagerLevelStreaming);
	}
}

#pragma endregion CVarLog