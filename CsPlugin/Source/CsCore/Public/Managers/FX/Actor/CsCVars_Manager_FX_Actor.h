// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorTransactions;
// Scoped Timers
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerCreatePool;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerUpdate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerUpdateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerAllocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerAllocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerDeallocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerDeallocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerSpawn;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerFXActorTransactions;
	// Scoped Timer
	extern CSCORE_API const Type LogManagerFXActorScopedTimer;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerCreatePool;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerUpdate;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerUpdateObject;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerAllocate;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerAllocateObject;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerDeallocate;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerDeallocateObject;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerSpawn;
	extern CSCORE_API const Type LogManagerFXActorScopedTimerDestroy;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorTransactions);
		// Scoped Timer
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerCreatePool);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerUpdate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerUpdateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerAllocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerAllocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerDeallocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerDeallocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerSpawn);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerFXActor;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerFXActor);
	}
}

#pragma endregion ScopedGroup