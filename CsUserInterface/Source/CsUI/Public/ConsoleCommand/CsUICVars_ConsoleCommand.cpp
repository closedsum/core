// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "ConsoleCommand/CsUICVars_ConsoleCommand.h"

TAutoConsoleVariable<bool> CsUICVarEnableConsoleCommandUI(
	TEXT("enable.consolecommand.ui"),
	0,
	TEXT("Enable Console Command UI."),
	ECVF_SetByConsole
);

// CVarToggle
#pragma region

namespace NCsCVarToggle
{
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(EnableConsoleCommandUI, "Enable Console Command UI");

	namespace Map
	{
		CSUI_API CS_ADD_TO_CVAR_MAP(EnableConsoleCommandUI, CsUICVarEnableConsoleCommandUI);
	}
}

#pragma endregion CVarToggle