// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Actor/CsCVars_Manager_FX.h"

TAutoConsoleVariable<int32> CsCVarLogManagerFXTransactions(
	TEXT("log.manager.fx.transactions"),
	0,
	TEXT("Log Manager FX Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimer(
	TEXT("log.manager.fx.scopedtimer"),
	0,
	TEXT("Log Manager FX Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerCreatePool(
	TEXT("log.manager.fx.scopedtimer.createpool"),
	0,
	TEXT("Log Manager FX Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerUpdate(
	TEXT("log.manager.fx.scopedtimer.update"),
	0,
	TEXT("Log Manager FX Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerUpdateObject(
	TEXT("log.manager.fx.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager FX Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerAllocate(
	TEXT("log.manager.fx.scopedtimer.allocate"),
	0,
	TEXT("Log Manager FX Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerAllocateObject(
	TEXT("log.manager.fx.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager FX Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDeallocate(
	TEXT("log.manager.fx.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager FX Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDeallocateObject(
	TEXT("log.manager.fx.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager FX Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerSpawn(
	TEXT("log.manager.fx.scopedtimer.spawn"),
	0,
	TEXT("Log Manager FX Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerFXScopedTimerDestroy(
	TEXT("log.manager.fx.scopedtimer.destroy"),
	0, 
	TEXT("Log Manager FX Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXTransactions, "Log Manager FX Transactions");
	// Scoped Timer
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimer, "Log Manager FX Scoped Timer");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerCreatePool, "Log Manager FX Scoped Timer Create Pool");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerUpdate, "Log Manager FX Scoped Timer Update");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerUpdateObject, "Log Manager FX Scoped Timer Update Object");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerAllocate, "Log Manager FX Scoped Allocate");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerAllocateObject, "Log Manager FX Scoped Allocate Object");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerDeallocate, "Log Manager FX Scoped Timer Deallocate");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerDeallocateObject, "Log Manager FX Scoped Timer Deallocate Object");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerSpawn, "Log Manager FX Scoped Timer Spawn");
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerFXScopedTimerDestroy, "Log Manager FX Scoped Timer Destroy");


	namespace Map
	{
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXTransactions, CsCVarLogManagerFXTransactions);
		// Scoped Timer
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimer, CsCVarLogManagerFXScopedTimer);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerCreatePool, CsCVarLogManagerFXScopedTimerCreatePool);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerUpdate, CsCVarLogManagerFXScopedTimerUpdate);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerUpdateObject, CsCVarLogManagerFXScopedTimerUpdateObject);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerAllocate, CsCVarLogManagerFXScopedTimerAllocate);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerAllocateObject, CsCVarLogManagerFXScopedTimerAllocateObject);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDeallocate, CsCVarLogManagerFXScopedTimerDeallocate);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDeallocateObject, CsCVarLogManagerFXScopedTimerDeallocateObject);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerSpawn, CsCVarLogManagerFXScopedTimerSpawn);
		CSFX_API CS_ADD_TO_CVAR_MAP(LogManagerFXScopedTimerDestroy, CsCVarLogManagerFXScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSFX_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerFX, "Manager FX");

	namespace Map
	{
		extern CSFX_API CS_ADD_TO_CVAR_MAP(ManagerFX, CsCVarLogManagerFXScopedTimer);
	}
}

#pragma endregion ScopedGroup