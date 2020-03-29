// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Managers
#pragma region

	// Widget
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetTransactions;

#pragma endregion Widget

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Widget
	extern CSCOREDEPRECATED_API const Type LogManagerWidgetTransactions;

	namespace Map
	{
		// Managers

			// Widget
	}
}

#pragma endregion CVarLog