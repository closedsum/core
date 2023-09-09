// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundTransactions;
// Scoped Timers
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerCreatePool;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerUpdate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerUpdateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerAllocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerAllocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDeallocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDeallocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerSpawn;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerSoundTransactions;
	// Scoped Timer
	extern CSCORE_API const Type LogManagerSoundScopedTimer;
	extern CSCORE_API const Type LogManagerSoundScopedTimerCreatePool;
	extern CSCORE_API const Type LogManagerSoundScopedTimerUpdate;
	extern CSCORE_API const Type LogManagerSoundScopedTimerUpdateObject;
	extern CSCORE_API const Type LogManagerSoundScopedTimerAllocate;
	extern CSCORE_API const Type LogManagerSoundScopedTimerAllocateObject;
	extern CSCORE_API const Type LogManagerSoundScopedTimerDeallocate;
	extern CSCORE_API const Type LogManagerSoundScopedTimerDeallocateObject;
	extern CSCORE_API const Type LogManagerSoundScopedTimerSpawn;
	extern CSCORE_API const Type LogManagerSoundScopedTimerDestroy;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundTransactions);
		// Scoped Timer
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerCreatePool);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerUpdate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerUpdateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerAllocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerAllocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDeallocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDeallocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerSpawn);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerSound;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerSound);
	}
}

#pragma endregion ScopedGroup