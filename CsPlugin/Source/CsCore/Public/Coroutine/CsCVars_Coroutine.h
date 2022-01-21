// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineTransactions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineRunning;
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
	// Scoped Timer
	extern CSCORE_API const Type LogCoroutinesScopedTimer;
	extern CSCORE_API const Type LogRoutineScopedTimer;
	extern CSCORE_API const Type LogCoroutineScopedTimer;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineTransactions);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogCoroutineRunning);
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