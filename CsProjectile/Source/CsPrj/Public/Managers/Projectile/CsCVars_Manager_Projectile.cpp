// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsCVars_Manager_Projectile.h"

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileTransactions(
	TEXT("log.manager.projectile.transactions"),
	0,
	TEXT("Log Manager Projectile Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimer(
	TEXT("log.manager.projectile.scopedtimer"),
	0,
	TEXT("Log Manager Projectile Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerCreatePool(
	TEXT("log.manager.projectile.scopedtimer.createpool"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerUpdate(
	TEXT("log.manager.projectile.scopedtimer.update"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerUpdateObject(
	TEXT("log.manager.projectile.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerAllocate(
	TEXT("log.manager.projectile.scopedtimer.allocate"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerAllocateObject(
	TEXT("log.manager.projectile.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerDeallocate(
	TEXT("log.manager.projectile.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerDeallocateObject(
	TEXT("log.manager.projectile.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerSpawn(
	TEXT("log.manager.projectile.scopedtimer.spawn"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileScopedTimerDestroy(
	TEXT("log.manager.projectile.scopedtimer.destroy"),
	0,
	TEXT("Log Manager Projectile Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileTransactions, "Log Manager Projectile Transactions");
	// Scoped Timer
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimer, "Log Manager Projectile Scoped Timer");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerCreatePool, "Log Manager Projectile Scoped Timer Create Pool");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerUpdate, "Log Manager Projectile Scoped Timer Update");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerUpdateObject, "Log Manager Projectile Scoped Timer Update Object");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerAllocate, "Log Manager Projectile Scoped Allocate");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerAllocateObject, "Log Manager Projectile Scoped Allocate Object");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerDeallocate, "Log Manager Projectile Scoped Timer Deallocate");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerDeallocateObject, "Log Manager Projectile Scoped Timer Deallocate Object");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerSpawn, "Log Manager Projectile Scoped Timer Spawn");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileScopedTimerDestroy, "Log Manager Projectile Scoped Timer Destroy");

	namespace Map
	{
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileTransactions, CsCVarLogManagerProjectileTransactions);
		// Scoped Timer
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimer, CsCVarLogManagerProjectileScopedTimer);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerCreatePool, CsCVarLogManagerProjectileScopedTimerCreatePool);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerUpdate, CsCVarLogManagerProjectileScopedTimerUpdate);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerUpdateObject, CsCVarLogManagerProjectileScopedTimerUpdateObject);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerAllocate, CsCVarLogManagerProjectileScopedTimerAllocate);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerAllocateObject, CsCVarLogManagerProjectileScopedTimerAllocateObject);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerDeallocate, CsCVarLogManagerProjectileScopedTimerDeallocate);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerDeallocateObject, CsCVarLogManagerProjectileScopedTimerDeallocateObject);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerSpawn, CsCVarLogManagerProjectileScopedTimerSpawn);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileScopedTimerDestroy, CsCVarLogManagerProjectileScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsScopedGroup, ManagerProjectile, "Manager Projectile");

	namespace Map
	{
		extern CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsScopedGroupMap, ManagerProjectile, CsCVarLogManagerProjectileScopedTimer);
	}
}

#pragma endregion ScopedGroup