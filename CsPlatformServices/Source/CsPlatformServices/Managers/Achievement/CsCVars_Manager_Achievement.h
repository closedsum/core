// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Managers
#pragma region

	// Achievement
#pragma region

extern CSPLATFORMSERVICES_API TAutoConsoleVariable<int32> CsCVarLogManagerAchievementTransactions;

#pragma endregion Save

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Achievement
	extern CSPLATFORMSERVICES_API const Type LogManagerAchievementTransactions;

	namespace Map
	{
		// Managers

			// Achievement
		extern CSPLATFORMSERVICES_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerAchievementTransactions);
	}
}

#pragma endregion CVarLog