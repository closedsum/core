// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/SkeletalMesh/CsCVars_Manager_SkeletalMeshActor.h"

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorTransactions(
	TEXT("log.manager.SkeletalMeshactor.transactions"),
	0,
	TEXT("Log Manager SkeletalMeshActor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimer(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerCreatePool(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.createpool"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerUpdate(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.update"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerUpdateObject(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerAllocate(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.allocate"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerAllocateObject(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerDeallocate(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerDeallocateObject(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerSpawn(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.spawn"),
	0,
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerDestroy(
	TEXT("log.manager.SkeletalMeshactor.scopedtimer.destroy"),
	0, 
	TEXT("Log Manager SkeletalMeshActor Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorTransactions, "Log Manager SkeletalMeshActor Transactions");
	// Scoped Timer
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimer, "Log Manager SkeletalMeshActor Scoped Timer");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerCreatePool, "Log Manager SkeletalMeshActor Scoped Timer Create Pool");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerUpdate, "Log Manager SkeletalMeshActor Scoped Timer Update");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerUpdateObject, "Log Manager SkeletalMeshActor Scoped Timer Update Object");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerAllocate, "Log Manager SkeletalMeshActor Scoped Allocate");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerAllocateObject, "Log Manager SkeletalMeshActor Scoped Allocate Object");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerDeallocate, "Log Manager SkeletalMeshActor Scoped Timer Deallocate");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerDeallocateObject, "Log Manager SkeletalMeshActor Scoped Timer Deallocate Object");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerSpawn, "Log Manager SkeletalMeshActor Scoped Timer Spawn");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSkeletalMeshActorScopedTimerDestroy, "Log Manager SkeletalMeshActor Scoped Timer Destroy");


	namespace Map
	{
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorTransactions, CsCVarLogManagerSkeletalMeshActorTransactions);
		// Scoped Timer
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimer, CsCVarLogManagerSkeletalMeshActorScopedTimer);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerCreatePool, CsCVarLogManagerSkeletalMeshActorScopedTimerCreatePool);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerUpdate, CsCVarLogManagerSkeletalMeshActorScopedTimerUpdate);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerUpdateObject, CsCVarLogManagerSkeletalMeshActorScopedTimerUpdateObject);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerAllocate, CsCVarLogManagerSkeletalMeshActorScopedTimerAllocate);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerAllocateObject, CsCVarLogManagerSkeletalMeshActorScopedTimerAllocateObject);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerDeallocate, CsCVarLogManagerSkeletalMeshActorScopedTimerDeallocate);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerDeallocateObject, CsCVarLogManagerSkeletalMeshActorScopedTimerDeallocateObject);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerSpawn, CsCVarLogManagerSkeletalMeshActorScopedTimerSpawn);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerDestroy, CsCVarLogManagerSkeletalMeshActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerSkeletalMeshActor, "Manager SkeletalMeshActor");

	namespace Map
	{
		extern CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(ManagerSkeletalMeshActor, CsCVarLogManagerSkeletalMeshActorScopedTimer);
	}
}

#pragma endregion ScopedGroup