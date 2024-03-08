// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeSet;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeClear;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeCounter;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledWaitForSystemComplete;
// Scoped Timers
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXScopedTimerActivate;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogFXPooledChange;
	extern CSCORE_API const Type LogFXPooledChangeSet;
	extern CSCORE_API const Type LogFXPooledChangeClear;
	extern CSCORE_API const Type LogFXPooledChangeCounter;
	extern CSCORE_API const Type LogFXPooledWaitForSystemComplete;
	// Scoped Timer
	extern CSCORE_API const Type LogFXScopedTimer;
	extern CSCORE_API const Type LogFXScopedTimerActivate;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeSet);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeClear);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeCounter);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledWaitForSystemComplete);
		// Scoped Timer
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXScopedTimerActivate);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type FX;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(FX);
	}
}

#pragma endregion ScopedGroup