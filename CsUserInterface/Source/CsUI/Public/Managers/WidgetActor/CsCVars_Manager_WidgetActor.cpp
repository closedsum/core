// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/WidgetActor/CsCVars_Manager_WidgetActor.h"

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorTransactions(
	TEXT("log.manager.widget.actor.transactions"),
	0,
	TEXT("Log Manager Widget Actor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimer(
	TEXT("log.manager.widget.actor.scopedtimer"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerCreatePool(
	TEXT("log.manager.widget.actor.scopedtimer.createpool"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerUpdate(
	TEXT("log.manager.widget.actor.scopedtimer.update"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerUpdateObject(
	TEXT("log.manager.widget.actor.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerAllocate(
	TEXT("log.manager.widget.actor.scopedtimer.allocate"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerAllocateObject(
	TEXT("log.manager.widget.actor.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerDeallocate(
	TEXT("log.manager.widget.actor.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerDeallocateObject(
	TEXT("log.manager.widget.actor.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerSpawn(
	TEXT("log.manager.widget.actor.scopedtimer.spawn"),
	0,
	TEXT("Log Manager Widget Actor Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorScopedTimerDestroy(
	TEXT("log.manager.widget.actor.scopedtimer.destroy"),
	0, 
	TEXT("Log Manager Widget Actor Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorTransactions, "Log Manager Widget Actor Transactions");
	// Scoped Timer
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimer, "Log Manager Widget Actor Scoped Timer");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerCreatePool, "Log Manager Widget Actor Scoped Timer Create Pool");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerUpdate, "Log Manager Widget Actor Scoped Timer Update");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerUpdateObject, "Log Manager Widget Actor Scoped Timer Update Object");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerAllocate, "Log Manager Widget Actor Scoped Allocate");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerAllocateObject, "Log Manager Widget Actor Scoped Allocate Object");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerDeallocate, "Log Manager Widget Actor Scoped Timer Deallocate");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerDeallocateObject, "Log Manager Widget Actor Scoped Timer Deallocate Object");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerSpawn, "Log Manager Widget Actor Scoped Timer Spawn");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerWidgetActorScopedTimerDestroy, "Log Manager Widget Actor Scoped Timer Destroy");

	namespace Map
	{
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorTransactions, CsCVarLogManagerWidgetActorTransactions);
		// Scoped Timer
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimer, CsCVarLogManagerWidgetActorScopedTimer);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerCreatePool, CsCVarLogManagerWidgetActorScopedTimerCreatePool);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerUpdate, CsCVarLogManagerWidgetActorScopedTimerUpdate);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerUpdateObject, CsCVarLogManagerWidgetActorScopedTimerUpdateObject);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerAllocate, CsCVarLogManagerWidgetActorScopedTimerAllocate);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerAllocateObject, CsCVarLogManagerWidgetActorScopedTimerAllocateObject);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerDeallocate, CsCVarLogManagerWidgetActorScopedTimerDeallocate);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerDeallocateObject, CsCVarLogManagerWidgetActorScopedTimerDeallocateObject);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerSpawn, CsCVarLogManagerWidgetActorScopedTimerSpawn);
		CSUI_API CS_ADD_TO_CVAR_MAP(LogManagerWidgetActorScopedTimerDestroy, CsCVarLogManagerWidgetActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerWidgetActor, "Manager Widget Actor");

	namespace Map
	{
		extern CSUI_API CS_ADD_TO_CVAR_MAP(ManagerWidgetActor, CsCVarLogManagerWidgetActorScopedTimer);
	}
}

#pragma endregion ScopedGroup