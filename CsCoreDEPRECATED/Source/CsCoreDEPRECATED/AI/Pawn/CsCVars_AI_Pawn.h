// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// AI
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogManagerAITransactions;

#pragma endregion AI

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// AI

		// Interactive AI Pawn
	extern CSCOREDEPRECATED_API const Type LogInteractiveAIPawnPhysicsStateChange;

	namespace Map
	{
	}
}

#pragma endregion CVarLog