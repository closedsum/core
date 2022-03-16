// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/CsCVars_Manager_Weapon.h"

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponTransactions(
	TEXT("log.manager.character.transactions"),
	0,
	TEXT("Log Manager Weapon Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimer(
	TEXT("log.manager.character.scopedtimer"),
	0,
	TEXT("Log Manager Weapon Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerCreatePool(
	TEXT("log.manager.character.scopedtimer.createpool"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerUpdate(
	TEXT("log.manager.character.scopedtimer.update"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerUpdateObject(
	TEXT("log.manager.character.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerAllocate(
	TEXT("log.manager.character.scopedtimer.allocate"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerAllocateObject(
	TEXT("log.manager.character.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerDeallocate(
	TEXT("log.manager.character.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerDeallocateObject(
	TEXT("log.manager.character.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerSpawn(
	TEXT("log.manager.character.scopedtimer.spawn"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWeaponScopedTimerDestroy(
	TEXT("log.manager.character.scopedtimer.destroy"),
	0,
	TEXT("Log Manager Weapon Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponTransactions, "Log Manager Weapon Transactions");
	// Scoped Timer
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimer, "Log Manager Weapon Scoped Timer");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerCreatePool, "Log Manager Weapon Scoped Timer Create Pool");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerUpdate, "Log Manager Weapon Scoped Timer Update");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerUpdateObject, "Log Manager Weapon Scoped Timer Update Object");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerAllocate, "Log Manager Weapon Scoped Allocate");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerAllocateObject, "Log Manager Weapon Scoped Allocate Object");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerDeallocate, "Log Manager Weapon Scoped Timer Deallocate");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerDeallocateObject, "Log Manager Weapon Scoped Timer Deallocate Object");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerSpawn, "Log Manager Weapon Scoped Timer Spawn");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWeaponScopedTimerDestroy, "Log Manager Weapon Scoped Timer Destroy");

	namespace Map
	{
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponTransactions, CsCVarLogManagerWeaponTransactions);
		// Scoped Timer
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimer, CsCVarLogManagerWeaponScopedTimer);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerCreatePool, CsCVarLogManagerWeaponScopedTimerCreatePool);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerUpdate, CsCVarLogManagerWeaponScopedTimerUpdate);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerUpdateObject, CsCVarLogManagerWeaponScopedTimerUpdateObject);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerAllocate, CsCVarLogManagerWeaponScopedTimerAllocate);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerAllocateObject, CsCVarLogManagerWeaponScopedTimerAllocateObject);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerDeallocate, CsCVarLogManagerWeaponScopedTimerDeallocate);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerDeallocateObject, CsCVarLogManagerWeaponScopedTimerDeallocateObject);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerSpawn, CsCVarLogManagerWeaponScopedTimerSpawn);
		CSWP_API CS_ADD_TO_CVAR_MAP(LogManagerWeaponScopedTimerDestroy, CsCVarLogManagerWeaponScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerWeapon, "Manager Weapon");

	namespace Map
	{
		extern CSWP_API CS_ADD_TO_CVAR_MAP(ManagerWeapon, CsCVarLogManagerWeaponScopedTimer);
	}
}

#pragma endregion ScopedGroup