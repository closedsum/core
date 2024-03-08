// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSUI_API TAutoConsoleVariable<bool> CsUICVarEnableConsoleCommandUI;

// CVarToggle
#pragma region

namespace NCsCVarToggle
{
	extern CSUI_API const Type EnableConsoleCommandUI;

	namespace Map
	{
		extern CSUI_API CS_DECLARE_ADD_TO_CVAR_MAP(EnableConsoleCommandUI);
	}
}

#pragma endregion CVarToggle