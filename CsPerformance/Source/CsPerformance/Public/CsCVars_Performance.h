// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSPERFORMANCE_API TAutoConsoleVariable<bool> CsCVarShowPerformanceFPS;

// CVarToggle
#pragma region

namespace NCsCVarToggle
{
	extern CSPERFORMANCE_API const Type ShowPerformanceFPS;

	namespace Map
	{
		extern CSPERFORMANCE_API CS_DECLARE_ADD_TO_CVAR_MAP(ShowPerformanceFPS);
	}
}

#pragma endregion CVarToggle