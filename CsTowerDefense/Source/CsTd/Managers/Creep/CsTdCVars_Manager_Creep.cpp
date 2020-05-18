// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/CsTdCVars_Manager_Creep.h"

TAutoConsoleVariable<int32> CsTdCVarLogManagerCreepTransactions(
	TEXT("log.manager.creep.transactions"),
	0,
	TEXT("[Non-Shipping] Log Manager Creep Transactions"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsTdCVarEnableManagerCreepUnitTest(
	TEXT("enable.manager.creep.unittest"),
	0,
	TEXT("[Non-Shipping] Enable Manager Creep Unit Test"),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSTD_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerCreepTransactions, "Log Manager Creep Transactions");

	namespace Map
	{
		CSTD_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerCreepTransactions, CsTdCVarLogManagerCreepTransactions);
	}
}

#pragma endregion CVarLog

// CVarToggle
#pragma region

namespace NCsCVarToggle
{
	CSTD_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarToggle, EnableManagerCreepUnitTest, "Enable Manager Creep Unit Test");

	namespace Map
	{
		CSTD_API CS_ADD_TO_CVAR_MAP(FCsCVarToggleMap, EnableManagerCreepUnitTest, CsTdCVarEnableManagerCreepUnitTest);
	}
}

#pragma endregion CVarToggle