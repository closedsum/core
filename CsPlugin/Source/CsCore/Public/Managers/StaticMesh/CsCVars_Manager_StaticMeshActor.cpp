// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/CsCVars_Manager_StaticMeshActor.h"

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorTransactions(
	TEXT("log.manager.staticmeshactor.transactions"),
	0,
	TEXT("Log Manager StaticMeshActor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimer(
	TEXT("log.manager.staticmeshactor.scopedtimer"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerCreatePool(
	TEXT("log.manager.staticmeshactor.scopedtimer.createpool"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerUpdate(
	TEXT("log.manager.staticmeshactor.scopedtimer.update"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerUpdateObject(
	TEXT("log.manager.staticmeshactor.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerAllocate(
	TEXT("log.manager.staticmeshactor.scopedtimer.allocate"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerAllocateObject(
	TEXT("log.manager.staticmeshactor.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDeallocate(
	TEXT("log.manager.staticmeshactor.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDeallocateObject(
	TEXT("log.manager.staticmeshactor.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerSpawn(
	TEXT("log.manager.staticmeshactor.scopedtimer.spawn"),
	0,
	TEXT("Log Manager StaticMeshActor Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDestroy(
	TEXT("log.manager.staticmeshactor.scopedtimer.destroy"),
	0, 
	TEXT("Log Manager StaticMeshActor Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorTransactions, "Log Manager StaticMeshActor Transactions");
	// Scoped Timer
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimer, "Log Manager StaticMeshActor Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerCreatePool, "Log Manager StaticMeshActor Scoped Timer Create Pool");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerUpdate, "Log Manager StaticMeshActor Scoped Timer Update");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerUpdateObject, "Log Manager StaticMeshActor Scoped Timer Update Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerAllocate, "Log Manager StaticMeshActor Scoped Allocate");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerAllocateObject, "Log Manager StaticMeshActor Scoped Allocate Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerDeallocate, "Log Manager StaticMeshActor Scoped Timer Deallocate");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerDeallocateObject, "Log Manager StaticMeshActor Scoped Timer Deallocate Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerSpawn, "Log Manager StaticMeshActor Scoped Timer Spawn");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerDestroy, "Log Manager StaticMeshActor Scoped Timer Destroy");


	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorTransactions, CsCVarLogManagerStaticMeshActorTransactions);
		// Scoped Timer
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimer, CsCVarLogManagerStaticMeshActorScopedTimer);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerCreatePool, CsCVarLogManagerStaticMeshActorScopedTimerCreatePool);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerUpdate, CsCVarLogManagerStaticMeshActorScopedTimerUpdate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerUpdateObject, CsCVarLogManagerStaticMeshActorScopedTimerUpdateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerAllocate, CsCVarLogManagerStaticMeshActorScopedTimerAllocate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerAllocateObject, CsCVarLogManagerStaticMeshActorScopedTimerAllocateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerDeallocate, CsCVarLogManagerStaticMeshActorScopedTimerDeallocate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerDeallocateObject, CsCVarLogManagerStaticMeshActorScopedTimerDeallocateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerSpawn, CsCVarLogManagerStaticMeshActorScopedTimerSpawn);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerStaticMeshActorScopedTimerDestroy, CsCVarLogManagerStaticMeshActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerStaticMeshActor, "Manager StaticMeshActor");

	namespace Map
	{
		extern CSCORE_API CS_ADD_TO_CVAR_MAP(FCsScopedGroupMap, ManagerStaticMeshActor, CsCVarLogManagerStaticMeshActorScopedTimer);
	}
}

#pragma endregion ScopedGroup