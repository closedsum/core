// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Beam/CsCVars_Manager_Beam.h"

TAutoConsoleVariable<int32> CsCVarLogManagerBeamTransactions(
	TEXT("log.manager.beam.transactions"),
	0,
	TEXT("Log Manager Beam Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimer(
	TEXT("log.manager.beam.scopedtimer"),
	0,
	TEXT("Log Manager Beam Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerCreatePool(
	TEXT("log.manager.beam.scopedtimer.createpool"),
	0,
	TEXT("Log Manager Beam Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerUpdate(
	TEXT("log.manager.beam.scopedtimer.update"),
	0,
	TEXT("Log Manager Beam Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerUpdateObject(
	TEXT("log.manager.beam.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager Beam Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerAllocate(
	TEXT("log.manager.beam.scopedtimer.allocate"),
	0,
	TEXT("Log Manager Beam Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerAllocateObject(
	TEXT("log.manager.beam.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager Beam Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerDeallocate(
	TEXT("log.manager.beam.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager Beam Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerDeallocateObject(
	TEXT("log.manager.beam.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager Beam Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerSpawn(
	TEXT("log.manager.beam.scopedtimer.spawn"),
	0,
	TEXT("Log Manager Beam Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerBeamScopedTimerDestroy(
	TEXT("log.manager.beam.scopedtimer.destroy"),
	0,
	TEXT("Log Manager Beam Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamTransactions, "Log Manager Beam Transactions");
	// Scoped Timer
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimer, "Log Manager Beam Scoped Timer");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerCreatePool, "Log Manager Beam Scoped Timer Create Pool");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerUpdate, "Log Manager Beam Scoped Timer Update");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerUpdateObject, "Log Manager Beam Scoped Timer Update Object");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerAllocate, "Log Manager Beam Scoped Allocate");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerAllocateObject, "Log Manager Beam Scoped Allocate Object");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerDeallocate, "Log Manager Beam Scoped Timer Deallocate");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerDeallocateObject, "Log Manager Beam Scoped Timer Deallocate Object");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerSpawn, "Log Manager Beam Scoped Timer Spawn");
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerBeamScopedTimerDestroy, "Log Manager Beam Scoped Timer Destroy");

	namespace Map
	{
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamTransactions, CsCVarLogManagerBeamTransactions);
		// Scoped Timer
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimer, CsCVarLogManagerBeamScopedTimer);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerCreatePool, CsCVarLogManagerBeamScopedTimerCreatePool);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerUpdate, CsCVarLogManagerBeamScopedTimerUpdate);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerUpdateObject, CsCVarLogManagerBeamScopedTimerUpdateObject);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerAllocate, CsCVarLogManagerBeamScopedTimerAllocate);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerAllocateObject, CsCVarLogManagerBeamScopedTimerAllocateObject);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerDeallocate, CsCVarLogManagerBeamScopedTimerDeallocate);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerDeallocateObject, CsCVarLogManagerBeamScopedTimerDeallocateObject);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerSpawn, CsCVarLogManagerBeamScopedTimerSpawn);
		CSBEAM_API CS_ADD_TO_CVAR_MAP(LogManagerBeamScopedTimerDestroy, CsCVarLogManagerBeamScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSBEAM_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerBeam, "Manager Beam");

	namespace Map
	{
		extern CSBEAM_API CS_ADD_TO_CVAR_MAP(ManagerBeam, CsCVarLogManagerBeamScopedTimer);
	}
}

#pragma endregion ScopedGroup