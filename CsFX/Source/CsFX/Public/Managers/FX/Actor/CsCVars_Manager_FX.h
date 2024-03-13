// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXTransactions;
// Scoped Timers
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimer;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerCreatePool;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerUpdate;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerUpdateObject;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerAllocate;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerAllocateObject;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDeallocate;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDeallocateObject;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerSpawn;
extern CSFX_API TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSFX_API const Type LogManagerFXTransactions;
	// Scoped Timer
	extern CSFX_API const Type LogManagerFXScopedTimer;
	extern CSFX_API const Type LogManagerFXScopedTimerCreatePool;
	extern CSFX_API const Type LogManagerFXScopedTimerUpdate;
	extern CSFX_API const Type LogManagerFXScopedTimerUpdateObject;
	extern CSFX_API const Type LogManagerFXScopedTimerAllocate;
	extern CSFX_API const Type LogManagerFXScopedTimerAllocateObject;
	extern CSFX_API const Type LogManagerFXScopedTimerDeallocate;
	extern CSFX_API const Type LogManagerFXScopedTimerDeallocateObject;
	extern CSFX_API const Type LogManagerFXScopedTimerSpawn;
	extern CSFX_API const Type LogManagerFXScopedTimerDestroy;

	namespace Map
	{
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXTransactions);
		// Scoped Timer
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimer);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerCreatePool);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerUpdate);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerUpdateObject);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerAllocate);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerAllocateObject);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDeallocate);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDeallocateObject);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerSpawn);
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSFX_API const Type ManagerFX;

	namespace Map
	{
		extern CSFX_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerFX);
	}
}

#pragma endregion ScopedGroup