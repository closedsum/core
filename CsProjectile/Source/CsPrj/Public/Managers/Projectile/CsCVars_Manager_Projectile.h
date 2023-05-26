// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileTransactions;
// Scoped Timers
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimer;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerCreatePool;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerUpdate;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerUpdateObject;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerAllocate;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerAllocateObject;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerDeallocate;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerDeallocateObject;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerSpawn;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSPRJ_API const Type LogManagerProjectileTransactions;
	// Scoped Timer
	extern CSPRJ_API const Type LogManagerProjectileScopedTimer;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerCreatePool;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerUpdate;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerUpdateObject;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerAllocate;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerAllocateObject;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerDeallocate;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerDeallocateObject;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerSpawn;
	extern CSPRJ_API const Type LogManagerProjectileScopedTimerDestroy;

	namespace Map
	{
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileTransactions);
		// Scoped Timer
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimer);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerCreatePool);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerUpdate);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerUpdateObject);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerAllocate);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerAllocateObject);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerDeallocate);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerDeallocateObject);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerSpawn);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSPRJ_API const Type ManagerProjectile;

	namespace Map
	{
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerProjectile);
	}
}

#pragma endregion ScopedGroup