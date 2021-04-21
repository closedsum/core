// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// Managers
#pragma region

	// Save
#pragma region

extern CSPLATFORMSERVICES_API TAutoConsoleVariable<int32> CsCVarLogManagerSaveTransactions;

#pragma endregion Save

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Managers

		// Save
	extern CSPLATFORMSERVICES_API const Type LogManagerSaveTransactions;

	namespace Map
	{
		// Managers

			// Save
		extern CSPLATFORMSERVICES_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSaveTransactions);
	}
}

#pragma endregion CVarLog