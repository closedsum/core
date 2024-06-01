// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSCOROUTINE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineTransactions;
extern CSCOROUTINE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineRunning;
extern CSCOROUTINE_API TAutoConsoleVariable<int32> CsCVarLogRoutineEnd;
// Scoped Timer
extern CSCOROUTINE_API TAutoConsoleVariable<int32> CsCVarLogCoroutinesScopedTimer;
extern CSCOROUTINE_API TAutoConsoleVariable<int32> CsCVarLogRoutineScopedTimer;
extern CSCOROUTINE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineScopedTimer;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCOROUTINE_API const Type LogCoroutineTransactions;
	extern CSCOROUTINE_API const Type LogCoroutineRunning;
	extern CSCOROUTINE_API const Type LogRoutineEnd;
	// Scoped Timer
	extern CSCOROUTINE_API const Type LogCoroutinesScopedTimer;
	extern CSCOROUTINE_API const Type LogRoutineScopedTimer;
	extern CSCOROUTINE_API const Type LogCoroutineScopedTimer;

	namespace Map
	{
		extern CSCOROUTINE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineTransactions);
		extern CSCOROUTINE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineRunning);
		extern CSCOROUTINE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogRoutineEnd);
		// Scoped Timer
		extern CSCOROUTINE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutinesScopedTimer);
		extern CSCOROUTINE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogRoutineScopedTimer);
		extern CSCOROUTINE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineScopedTimer);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCOROUTINE_API const Type Coroutine;

	namespace Map
	{
		extern CSCOROUTINE_API CS_DECLARE_ADD_TO_CVAR_MAP(Coroutine);
	}
}

#pragma endregion ScopedGroup