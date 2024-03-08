// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXTransactions;
// Scoped Timers
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerCreatePool;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerUpdate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerUpdateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerAllocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerAllocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDeallocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDeallocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerSpawn;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerFXTransactions;
	// Scoped Timer
	extern CSCORE_API const Type LogManagerFXScopedTimer;
	extern CSCORE_API const Type LogManagerFXScopedTimerCreatePool;
	extern CSCORE_API const Type LogManagerFXScopedTimerUpdate;
	extern CSCORE_API const Type LogManagerFXScopedTimerUpdateObject;
	extern CSCORE_API const Type LogManagerFXScopedTimerAllocate;
	extern CSCORE_API const Type LogManagerFXScopedTimerAllocateObject;
	extern CSCORE_API const Type LogManagerFXScopedTimerDeallocate;
	extern CSCORE_API const Type LogManagerFXScopedTimerDeallocateObject;
	extern CSCORE_API const Type LogManagerFXScopedTimerSpawn;
	extern CSCORE_API const Type LogManagerFXScopedTimerDestroy;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXTransactions);
		// Scoped Timer
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerCreatePool);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerUpdate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerUpdateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerAllocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerAllocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDeallocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDeallocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerSpawn);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerFX;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerFX);
	}
}

#pragma endregion ScopedGroup