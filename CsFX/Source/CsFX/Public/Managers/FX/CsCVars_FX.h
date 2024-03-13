// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChange;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeSet;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeClear;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeCounter;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogFXPooledWaitForSystemComplete;
// Scoped Timers
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogFXScopedTimer;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogFXScopedTimerActivate;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSFX_API const Type LogFXPooledChange;
	extern CSFX_API const Type LogFXPooledChangeSet;
	extern CSFX_API const Type LogFXPooledChangeClear;
	extern CSFX_API const Type LogFXPooledChangeCounter;
	extern CSFX_API const Type LogFXPooledWaitForSystemComplete;
	// Scoped Timer
	extern CSFX_API const Type LogFXScopedTimer;
	extern CSFX_API const Type LogFXScopedTimerActivate;

	namespace Map
	{
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChange);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeSet);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeClear);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeCounter);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledWaitForSystemComplete);
		// Scoped Timer
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXScopedTimer);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXScopedTimerActivate);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSFX_API const Type FX;

	namespace Map
	{
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(FX);
	}
}

#pragma endregion ScopedGroup