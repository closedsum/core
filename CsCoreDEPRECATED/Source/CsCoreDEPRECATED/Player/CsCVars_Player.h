// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// OnBoard
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogPlayerStateOnBoard;

#pragma endregion OnBoard

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Player

		// OnBoard
	extern CSCOREDEPRECATED_API const Type LogPlayerStateOnBoard;

	namespace Map
	{
	}
}

#pragma endregion CVarLog