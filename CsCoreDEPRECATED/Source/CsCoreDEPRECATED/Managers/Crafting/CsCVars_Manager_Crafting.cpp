// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Crafting/CsCVars_Manager_Crafting.h"

// Managers
#pragma region

	// Crafting
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerCraftingTransactions(
	TEXT("log.manager.crafting.transactions"),
	0,
	TEXT("Log Manager Crafting Begin, Craft, and Finish."),
	ECVF_SetByConsole
);

#pragma endregion Crafting

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Crafting
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagersCraftingTransactions);

	namespace Map
	{
	}
}

#pragma endregion CVarLog