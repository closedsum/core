// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Managers
#pragma region

	// AI
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogManagerAITransactions;

#pragma endregion AI

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// AI
	extern CSCOREDEPRECATED_API const Type LogManagerAITransactions;

	namespace Map
	{
	}
}

#pragma endregion CVarLog