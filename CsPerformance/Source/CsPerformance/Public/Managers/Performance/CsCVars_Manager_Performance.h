// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars_Core.h"

extern CSPERFORMANCE_API TAutoConsoleVariable<int32> CsCVarLogManagerPerformance;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSPERFORMANCE_API const Type LogManagerPerformance;

	namespace Map
	{
		extern CSPERFORMANCE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerPerformance);
	}
}

#pragma endregion CVarLog