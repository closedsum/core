// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/CsCVars_FX.h"

TAutoConsoleVariable<int32> CsCVarLogFXPooledChange(
	TEXT("log.fx.pooled.change"),
	0,
	TEXT("Log FX Pooled Changes (Preserved between Allocate and Deallocate)\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("Log a pooled FX changes preserved (NO CHANGE) between Allocate and Deallocate\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeSet(
	TEXT("log.fx.pooled.change.set"),
	0,
	TEXT("Log FX Pooled Changes Set (Between Allocate and Deallocate)\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("Log a pooled FX changes set (CHANGED) between Allocate and Deallocate\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeClear(
	TEXT("log.fx.pooled.change.clear"),
	0,
	TEXT("Log FX Pooled Changes Clear (Between Allocate and Deallocate)\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("Log a pooled FX changes cleared (RESET) between Allocate and Deallocate\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeCounter(
	TEXT("log.fx.pooled.change.counter"),
	0,
	TEXT("Log FX Pooled Changes Counter (Between Allocate and Deallocate)\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("Log a pooled FX the number of changes between Allocate and Deallocate\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXPooledWaitForSystemComplete(
	TEXT("log.fx.pooled.waitforsystemcomplete"),
	0,
	TEXT("Log FX Pooled Wait for System Complete\n")
	TEXT("\n")
	TEXT("[Non-Shipping]\n")
	TEXT("Log any waits initiated on the GameThread when a pooled FX\n")
	TEXT(" is waiting to complete / shutdown.\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogFXScopedTimer(
	TEXT("log.fx.scopedtimer"),
	0,
	TEXT("Log FX Scoped Timer\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogFXScopedTimerActivate(
	TEXT("log.fx.scopedtimer.activate"),
	0,
	TEXT("Log FX Scoped Timer Activate()\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledChange, "Log FX Pooled Changes (Preserved between Allocate and Deallocate)");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledChangeSet, "Log FX Pooled Changes Set (Between Allocate and Deallocate)");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledChangeClear, "Log FX Pooled Changes Clear (Between Allocate and Deallocate)");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledChangeCounter, "Log FX Pooled Changes Counter (Between Allocate and Deallocate)");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXPooledWaitForSystemComplete, "Log FX Pooled Wait for System Complete");
	// Scoped Timer
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXScopedTimer, "Log FX Scoped Timer");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogFXScopedTimerActivate, "Log FX Scoped Timer Activate()");

	namespace Map
	{
		CSFX_API CS_ADD_TO_CVAR_MAP(LogFXPooledChange, CsCVarLogFXPooledChange);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogFXPooledChangeSet, CsCVarLogFXPooledChangeSet);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogFXPooledChangeClear, CsCVarLogFXPooledChangeClear);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogFXPooledChangeCounter, CsCVarLogFXPooledChangeCounter);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogFXPooledWaitForSystemComplete, CsCVarLogFXPooledWaitForSystemComplete);
		// Scoped Timer
		CSFX_API CS_ADD_TO_CVAR_MAP(LogFXScopedTimer, CsCVarLogFXScopedTimer);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogFXScopedTimerActivate, CsCVarLogFXScopedTimerActivate);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(FX, "FX");

	namespace Map
	{
		extern CSFX_API CS_ADD_TO_CVAR_MAP(FX, CsCVarLogFXScopedTimer);
	}
}

#pragma endregion ScopedGroup