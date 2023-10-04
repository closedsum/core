// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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