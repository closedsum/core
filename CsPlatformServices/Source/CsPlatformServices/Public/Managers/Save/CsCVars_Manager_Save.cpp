// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars_Manager_Save.h"

// Managers
#pragma region

	// Save
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerSaveTransactions(
	TEXT("log.manager.save.transactions"),
	0,
	TEXT("Log Manager Save Transactions."),
	ECVF_SetByConsole | ECVF_SetByCode
);

#pragma endregion Save

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Save
	CSPLATFORMSERVICES_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSaveTransactions, "Log Manager Save Transactions");

	namespace Map
	{
		// Managers

			// Save
		CSPLATFORMSERVICES_API CS_ADD_TO_CVAR_MAP(LogManagerSaveTransactions, CsCVarLogManagerSaveTransactions);
	}
}

#pragma endregion CVarLog