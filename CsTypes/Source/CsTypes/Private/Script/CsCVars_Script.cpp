// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Script/CsCVars_Script.h"

// Script
#pragma region

TAutoConsoleVariable<int32> CsCVarLogOverrideFunctions(
	TEXT("log.override.functions"),
	0,
	TEXT("Log Override Functions used by Script."),
	ECVF_SetByConsole
);

#pragma endregion Script

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Script
	CSTYPES_API CS_CREATE_ENUM_STRUCT(LogOverrideFunctions);

	namespace Map
	{
		// Script
		CSTYPES_API CS_ADD_TO_CVAR_MAP(LogOverrideFunctions, CsCVarLogOverrideFunctions);
	}
}

#pragma endregion CVarLog

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
	CSTYPES_API CS_CREATE_ENUM_STRUCT_CUSTOM(EnableScriptChecked, "Enable Script Checked");

	namespace Map
	{
		CSTYPES_API CS_ADD_TO_CVAR_MAP(EnableScriptChecked, CsCVarEnableScriptChecked);
	}
}

#pragma endregion CVarToggle