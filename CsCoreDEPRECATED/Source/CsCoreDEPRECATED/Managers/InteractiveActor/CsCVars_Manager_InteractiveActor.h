// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Managers
#pragma region

	// Interactive Actor
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogInteractiveActorPhysicsStateChange;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogManagerInteractiveActorTransactions;

#pragma endregion Interactive Actor

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Interactive Actor
	extern CSCOREDEPRECATED_API const Type LogInteractiveActorPhysicsStateChange;
	extern CSCOREDEPRECATED_API const Type LogManagerInteractiveActorTransactions;

	namespace Map
	{
		// Managers

			// Interactive Actor
	}
}

#pragma endregion CVarLog