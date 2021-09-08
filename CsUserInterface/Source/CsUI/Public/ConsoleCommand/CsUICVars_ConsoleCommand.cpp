// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "ConsoleCommand/CsUICVars_ConsoleCommand.h"

TAutoConsoleVariable<int32> CsUICVarEnableConsoleCommandUI(
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