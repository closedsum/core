// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Script/CsCVars_Script.h"

TAutoConsoleVariable<bool> CsCVarEnableScriptChecked(
	TEXT("enable.script.checked"),
	0,
	TEXT("Enable Script Checked versions of functions. \n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("Script Checked versions by default use the 'safe' versions for Editor unless set to true.\n")
	TEXT("0 - (default) DISABLE	safe.\n")
	TEXT("1 -			ENABLE	checked."),
	ECVF_SetByConsole
);

// CVarToggle
#pragma region

namespace NCsCVarToggle
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EnableScriptChecked, "Enable Script Checked");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(EnableScriptChecked, CsCVarEnableScriptChecked);
	}
}

#pragma endregion CVarToggle