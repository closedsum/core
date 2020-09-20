// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsCVars_Manager_FX_Actor.h"

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorTransactions(
	TEXT("log.manager.fx.actor.transactions"),
	0,
	TEXT("Log Manager FX Actor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimer(
	TEXT("log.manager.fx.actor.scopedtimer"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerCreatePool(
	TEXT("log.manager.fx.actor.scopedtimer.createpool"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerUpdate(
	TEXT("log.manager.fx.actor.scopedtimer.update"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerUpdateObject(
	TEXT("log.manager.fx.actor.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerAllocate(
	TEXT("log.manager.fx.actor.scopedtimer.allocate"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerAllocateObject(
	TEXT("log.manager.fx.actor.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerDeallocate(
	TEXT("log.manager.fx.actor.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerDeallocateObject(
	TEXT("log.manager.fx.actor.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerSpawn(
	TEXT("log.manager.fx.actor.scopedtimer.spawn"),
	0,
	TEXT("Log Manager FX Actor Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXActorScopedTimerDestroy(
	TEXT("log.manager.fx.actor.scopedtimer.destroy"),
	0, 
	TEXT("Log Manager FX Actor Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorTransactions, "Log Manager FX Actor Transactions");
	// Scoped Timer
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimer, "Log Manager FX Actor Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerCreatePool, "Log Manager FX Actor Scoped Timer Create Pool");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerUpdate, "Log Manager FX Actor Scoped Timer Update");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerUpdateObject, "Log Manager FX Actor Scoped Timer Update Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerAllocate, "Log Manager FX Actor Scoped Allocate");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerAllocateObject, "Log Manager FX Actor Scoped Allocate Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerDeallocate, "Log Manager FX Actor Scoped Timer Deallocate");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerDeallocateObject, "Log Manager FX Actor Scoped Timer Deallocate Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerSpawn, "Log Manager FX Actor Scoped Timer Spawn");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXActorScopedTimerDestroy, "Log Manager FX Actor Scoped Timer Destroy");


	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorTransactions, CsCVarLogManagerFXActorTransactions);
		// Scoped Timer
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimer, CsCVarLogManagerFXActorScopedTimer);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerCreatePool, CsCVarLogManagerFXActorScopedTimerCreatePool);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerUpdate, CsCVarLogManagerFXActorScopedTimerUpdate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerUpdateObject, CsCVarLogManagerFXActorScopedTimerUpdateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerAllocate, CsCVarLogManagerFXActorScopedTimerAllocate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerAllocateObject, CsCVarLogManagerFXActorScopedTimerAllocateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerDeallocate, CsCVarLogManagerFXActorScopedTimerDeallocate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerDeallocateObject, CsCVarLogManagerFXActorScopedTimerDeallocateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerSpawn, CsCVarLogManagerFXActorScopedTimerSpawn);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerFXActorScopedTimerDestroy, CsCVarLogManagerFXActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerFXActor, "Manager FX Actor");

	namespace Map
	{
		extern CSCORE_API CS_ADD_TO_CVAR_MAP(ManagerFXActor, CsCVarLogManagerFXActorScopedTimer);
	}
}

#pragma endregion ScopedGroup