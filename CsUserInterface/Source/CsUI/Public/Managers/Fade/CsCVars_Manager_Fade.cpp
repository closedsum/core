// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Fade/CsCVars_Manager_Fade.h"

TAutoConsoleVariable<int32> CsCVarLogManagerFade(
	TEXT("log.manager.fade"),
	0,
	TEXT("Log Manager Fade."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFade, "Log Manager Fade");

	namespace Map
	{
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerFade, CsCVarLogManagerFade);
	}
}

#pragma endregion CVarLog