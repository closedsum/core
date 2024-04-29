// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileTransactions, "Log Manager Projectile Transactions");
	// Scoped Timer
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimer, "Log Manager Projectile Scoped Timer");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerCreatePool, "Log Manager Projectile Scoped Timer Create Pool");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerUpdate, "Log Manager Projectile Scoped Timer Update");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerUpdateObject, "Log Manager Projectile Scoped Timer Update Object");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerAllocate, "Log Manager Projectile Scoped Allocate");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerAllocateObject, "Log Manager Projectile Scoped Allocate Object");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerDeallocate, "Log Manager Projectile Scoped Timer Deallocate");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerDeallocateObject, "Log Manager Projectile Scoped Timer Deallocate Object");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerSpawn, "Log Manager Projectile Scoped Timer Spawn");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerProjectileScopedTimerDestroy, "Log Manager Projectile Scoped Timer Destroy");

	namespace Map
	{
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileTransactions, CsCVarLogManagerProjectileTransactions);
		// Scoped Timer
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimer, CsCVarLogManagerProjectileScopedTimer);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerCreatePool, CsCVarLogManagerProjectileScopedTimerCreatePool);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerUpdate, CsCVarLogManagerProjectileScopedTimerUpdate);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerUpdateObject, CsCVarLogManagerProjectileScopedTimerUpdateObject);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerAllocate, CsCVarLogManagerProjectileScopedTimerAllocate);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerAllocateObject, CsCVarLogManagerProjectileScopedTimerAllocateObject);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerDeallocate, CsCVarLogManagerProjectileScopedTimerDeallocate);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerDeallocateObject, CsCVarLogManagerProjectileScopedTimerDeallocateObject);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerSpawn, CsCVarLogManagerProjectileScopedTimerSpawn);
		CSPRJ_API CS_ADD_TO_CVAR_MAP(LogManagerProjectileScopedTimerDestroy, CsCVarLogManagerProjectileScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerProjectile, "Manager Projectile");

	namespace Map
	{
		extern CSPRJ_API CS_ADD_TO_CVAR_MAP(ManagerProjectile, CsCVarLogManagerProjectileScopedTimer);
	}
}

#pragma endregion ScopedGroup