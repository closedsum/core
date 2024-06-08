// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars_Core.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerLevelStreaming;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	typedef FECsCVarLog Type;

	// Helper
	extern CSCORE_API const Type LogManagerLevelStreaming;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerLevelStreaming);
	}
}

#pragma endregion CVarLog