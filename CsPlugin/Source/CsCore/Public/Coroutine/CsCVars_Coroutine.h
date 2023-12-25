// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineTransactions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineRunning;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogRoutineEnd;
// Scoped Timer
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutinesScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogRoutineScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineScopedTimer;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogCoroutineTransactions;
	extern CSCORE_API const Type LogCoroutineRunning;
	extern CSCORE_API const Type LogRoutineEnd;
	// Scoped Timer
	extern CSCORE_API const Type LogCoroutinesScopedTimer;
	extern CSCORE_API const Type LogRoutineScopedTimer;
	extern CSCORE_API const Type LogCoroutineScopedTimer;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineTransactions);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineRunning);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogRoutineEnd);
		// Scoped Timer
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutinesScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogRoutineScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineScopedTimer);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type Coroutine;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(Coroutine);
	}
}

#pragma endregion ScopedGroup