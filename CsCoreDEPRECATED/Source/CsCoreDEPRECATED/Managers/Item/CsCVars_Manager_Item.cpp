// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Item/CsCVars_Manager_Item.h"

// Interactive Actor
#pragma region

TAutoConsoleVariable<int32> CsCVarManagerItemRebuild(
	TEXT("manager.item.rebuild"),
	0,
	TEXT("Manager Item Rebuild."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerItemTransactions(
	TEXT("log.manager.item.transactions"),
	0,
	TEXT("Log Manager Item Allocate and DeAllocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerItemActionGetFail(
	TEXT("log.manager.item.action.get.fail"),
	0,
	TEXT("Log Manager Item GetItem(s) failed retrieval of item."),
	ECVF_SetByConsole
);

#pragma endregion Interactive Actor

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Item
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerItemTransactions);
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerItemActionGetFail);

	namespace Map
	{
		// Managers

			// Interactive Actor
	}
}

#pragma endregion CVarLog