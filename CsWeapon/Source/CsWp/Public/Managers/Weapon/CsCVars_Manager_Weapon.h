// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponTransactions;
// Scoped Timers
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimer;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerCreatePool;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerUpdate;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerUpdateObject;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerAllocate;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerAllocateObject;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerDeallocate;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerDeallocateObject;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerSpawn;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSWP_API const Type LogManagerWeaponTransactions;
	// Scoped Timer
	extern CSWP_API const Type LogManagerWeaponScopedTimer;
	extern CSWP_API const Type LogManagerWeaponScopedTimerCreatePool;
	extern CSWP_API const Type LogManagerWeaponScopedTimerUpdate;
	extern CSWP_API const Type LogManagerWeaponScopedTimerUpdateObject;
	extern CSWP_API const Type LogManagerWeaponScopedTimerAllocate;
	extern CSWP_API const Type LogManagerWeaponScopedTimerAllocateObject;
	extern CSWP_API const Type LogManagerWeaponScopedTimerDeallocate;
	extern CSWP_API const Type LogManagerWeaponScopedTimerDeallocateObject;
	extern CSWP_API const Type LogManagerWeaponScopedTimerSpawn;
	extern CSWP_API const Type LogManagerWeaponScopedTimerDestroy;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponTransactions);
		// Scoped Timer
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimer);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerCreatePool);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerUpdate);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerUpdateObject);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerAllocate);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerAllocateObject);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerDeallocate);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerDeallocateObject);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerSpawn);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSWP_API const Type ManagerWeapon;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerWeapon);
	}
}

#pragma endregion ScopedGroup