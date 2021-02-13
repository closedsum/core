// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsCVars_FX.h"

TAutoConsoleVariable<int32> CsCVarLogFXPooledChange(
	TEXT("log.fx.pooled.change"),
	0,
	TEXT("Log FX Pooled Changes (Preserved between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeSet(
	TEXT("log.fx.pooled.change.set"),
	0,
	TEXT("Log FX Pooled Changes Set (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeClear(
	TEXT("log.fx.pooled.change.clear"),
	0,
	TEXT("Log FX Pooled Changes Clear (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeCounter(
	TEXT("log.fx.pooled.change.counter"),
	0,
	TEXT("Log FX Pooled Changes Counter (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

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
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledChange, "Log FX Pooled Changes (Preserved between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledChangeSet, "Log FX Pooled Changes Set (Between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledChangeClear, "Log FX Pooled Changes Clear (Between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledChangeCounter, "Log FX Pooled Changes Counter (Between Allocate and Deallocate)");
	// Scoped Timer
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXScopedTimer, "Log FX Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXScopedTimerActivate, "Log FX Scoped Timer Activate()");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogFXPooledChange, CsCVarLogFXPooledChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogFXPooledChangeSet, CsCVarLogFXPooledChangeSet);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogFXPooledChangeClear, CsCVarLogFXPooledChangeClear);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogFXPooledChangeCounter, CsCVarLogFXPooledChangeCounter);
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