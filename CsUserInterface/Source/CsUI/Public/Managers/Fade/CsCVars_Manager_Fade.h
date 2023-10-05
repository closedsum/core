// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSUI_API TAutoConsoleVariable<int32> CsCVarLogManagerFade;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSUI_API const Type LogManagerFade;

	namespace Map
	{
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFade);
	}
}

#pragma endregion CVarLog