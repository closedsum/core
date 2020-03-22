// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Managers
#pragma region

	// Crafting
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogManagerCraftingTransactions;

#pragma endregion Crafting

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Crafting
	extern CSCOREDEPRECATED_API const Type LogManagerCraftingTransactions;

	namespace Map
	{
	}
}

#pragma endregion CVarLog