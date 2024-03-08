// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsCVars_PlatformProcess.h"
#include "CsPlatformProcess.h"

TAutoConsoleVariable<int32> CsCVarLogManagerProcessTransactions(
	TEXT("log.manager.process.transactions"),
	0,
	TEXT("Log Manager Process Allocate and DeAllocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogProcessIO(
	TEXT("log.process.io"),
	0,
	TEXT("Log Process Input / Ouput from Write / Read Pipes."),
	ECVF_SetByConsole
);

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogManagerProcessTransactions);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogProcessIO);

	namespace Map
	{
	}
}