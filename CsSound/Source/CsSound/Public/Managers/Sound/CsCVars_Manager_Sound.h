// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundTransactions;
// Scoped Timers
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimer;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerCreatePool;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerUpdate;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerUpdateObject;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerAllocate;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerAllocateObject;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDeallocate;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDeallocateObject;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerSpawn;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSSOUND_API const Type LogManagerSoundTransactions;
	// Scoped Timer
	extern CSSOUND_API const Type LogManagerSoundScopedTimer;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerCreatePool;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerUpdate;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerUpdateObject;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerAllocate;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerAllocateObject;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerDeallocate;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerDeallocateObject;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerSpawn;
	extern CSSOUND_API const Type LogManagerSoundScopedTimerDestroy;

	namespace Map
	{
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundTransactions);
		// Scoped Timer
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimer);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerCreatePool);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerUpdate);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerUpdateObject);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerAllocate);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerAllocateObject);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDeallocate);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDeallocateObject);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerSpawn);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSSOUND_API const Type ManagerSound;

	namespace Map
	{
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerSound);
	}
}

#pragma endregion ScopedGroup