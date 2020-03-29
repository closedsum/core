// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Managers
#pragma region

	// Widget Actor
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorTransactions;

#pragma endregion Widget Actor

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Widget Actor
	extern CSCOREDEPRECATED_API const Type LogManagerWidgetActorTransactions;

	namespace Map
	{
		// Managers

			// Widget Actor
	}
}

#pragma endregion CVarLog