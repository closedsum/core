// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Load/CsCVars_Manager_Load.h"


TAutoConsoleVariable<int32> CsCVarLogManagerLoad(
	TEXT("log.manager.load"),
	0,
	TEXT("Log Manager Load"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarManagerLoadAsyncOrder(
	TEXT("manager.loading.asyncorder"),
	-1,
	TEXT("Set Load Async Order for Async Loading. -1 = UNSET, 0 = None (Bulk), 1 = FirstToAst, 2 = Bulk"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDisplayLoading(
	TEXT("display.loading"),
	0,
	TEXT("Display Loading on HUD"),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogManagerLoad);

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerLoad, CsCVarLogManagerLoad);
	}
}

#pragma endregion CVarLog