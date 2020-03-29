// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Managers
#pragma region

	// Item
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarManagerItemRebuild;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogManagerItemTransactions;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogManagerItemActionGetFail;

#pragma endregion Item

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Item
	extern CSCOREDEPRECATED_API const Type LogManagerItemTransactions;
	extern CSCOREDEPRECATED_API const Type LogManagerItemActionGetFail;

	namespace Map
	{
		// Managers

			// Item
	}
}

#pragma endregion CVarLog