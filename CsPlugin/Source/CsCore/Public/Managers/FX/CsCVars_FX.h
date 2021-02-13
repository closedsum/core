// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeSet;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeClear;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogFXPooledChangeCounter;
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
	// Scoped Timer
	extern CSCORE_API const Type LogFXScopedTimer;
	extern CSCORE_API const Type LogFXScopedTimerActivate;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeSet);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeClear);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogFXPooledChangeCounter);
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