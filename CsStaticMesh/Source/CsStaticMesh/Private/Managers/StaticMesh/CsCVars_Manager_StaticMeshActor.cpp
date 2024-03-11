// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorTransactions, "Log Manager StaticMeshActor Transactions");
	// Scoped Timer
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimer, "Log Manager StaticMeshActor Scoped Timer");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerCreatePool, "Log Manager StaticMeshActor Scoped Timer Create Pool");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerUpdate, "Log Manager StaticMeshActor Scoped Timer Update");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerUpdateObject, "Log Manager StaticMeshActor Scoped Timer Update Object");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerAllocate, "Log Manager StaticMeshActor Scoped Allocate");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerAllocateObject, "Log Manager StaticMeshActor Scoped Allocate Object");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerDeallocate, "Log Manager StaticMeshActor Scoped Timer Deallocate");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerDeallocateObject, "Log Manager StaticMeshActor Scoped Timer Deallocate Object");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerSpawn, "Log Manager StaticMeshActor Scoped Timer Spawn");
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerStaticMeshActorScopedTimerDestroy, "Log Manager StaticMeshActor Scoped Timer Destroy");


	namespace Map
	{
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorTransactions, CsCVarLogManagerStaticMeshActorTransactions);
		// Scoped Timer
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimer, CsCVarLogManagerStaticMeshActorScopedTimer);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerCreatePool, CsCVarLogManagerStaticMeshActorScopedTimerCreatePool);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerUpdate, CsCVarLogManagerStaticMeshActorScopedTimerUpdate);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerUpdateObject, CsCVarLogManagerStaticMeshActorScopedTimerUpdateObject);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerAllocate, CsCVarLogManagerStaticMeshActorScopedTimerAllocate);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerAllocateObject, CsCVarLogManagerStaticMeshActorScopedTimerAllocateObject);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDeallocate, CsCVarLogManagerStaticMeshActorScopedTimerDeallocate);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDeallocateObject, CsCVarLogManagerStaticMeshActorScopedTimerDeallocateObject);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerSpawn, CsCVarLogManagerStaticMeshActorScopedTimerSpawn);
		CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDestroy, CsCVarLogManagerStaticMeshActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSSTATICMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerStaticMeshActor, "Manager StaticMeshActor");

	namespace Map
	{
		extern CSSTATICMESH_API CS_ADD_TO_CVAR_MAP(ManagerStaticMeshActor, CsCVarLogManagerStaticMeshActorScopedTimer);
	}
}

#pragma endregion ScopedGroup