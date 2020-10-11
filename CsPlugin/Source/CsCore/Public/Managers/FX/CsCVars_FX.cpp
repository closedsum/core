// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsCVars_FX.h"

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogFXScopedTimer(
	TEXT("log.fx.scopedtimer"),
	0,
	TEXT("Log FX Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXScopedTimerActivate(
	TEXT("log.fx.scopedtimer.activate"),
	0,
	TEXT("Log FX Scoped Timer Activate()."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Scoped Timer
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXScopedTimer, "Log FX Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXScopedTimerActivate, "Log FX Scoped Timer Activate()");

	namespace Map
	{
		// Scoped Timer
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogFXScopedTimer, CsCVarLogFXScopedTimer);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogFXScopedTimerActivate, CsCVarLogFXScopedTimerActivate);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(FX, "FX");

	namespace Map
	{
		extern CSCORE_API CS_ADD_TO_CVAR_MAP(FX, CsCVarLogFXScopedTimer);
	}
}

#pragma endregion ScopedGroup