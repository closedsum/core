// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// AI
#pragma region

	// Behavior Tree
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogAIBTTasks;

#pragma endregion Behavior Tree

#pragma endregion AI

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// AI

		// Behavior Tree
	extern CSCOREDEPRECATED_API const Type LogAIBTTasks;

	namespace Map
	{
	}
}

#pragma endregion CVarLog