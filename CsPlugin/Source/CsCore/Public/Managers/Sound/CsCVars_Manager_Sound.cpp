// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsCVars_Manager_Sound.h"

TAutoConsoleVariable<int32> CsCVarLogManagerSoundTransactions(
	TEXT("log.manager.sound.transactions"),
	0,
	TEXT("Log Manager Sound Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// Scoped Timer

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimer(
	TEXT("log.manager.sound.scopedtimer"),
	0,
	TEXT("Log Manager Sound Scoped Timer."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerCreatePool(
	TEXT("log.manager.sound.scopedtimer.createpool"),
	0,
	TEXT("Log Manager Sound Scoped Timer Create Pool."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerUpdate(
	TEXT("log.manager.sound.scopedtimer.update"),
	0,
	TEXT("Log Manager Sound Scoped Timer Update."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerUpdateObject(
	TEXT("log.manager.sound.scopedtimer.updateobject"),
	0,
	TEXT("Log Manager Sound Scoped Timer Update Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerAllocate(
	TEXT("log.manager.sound.scopedtimer.allocate"),
	0,
	TEXT("Log Manager Sound Scoped Timer Allocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerAllocateObject(
	TEXT("log.manager.sound.scopedtimer.allocateobject"),
	0,
	TEXT("Log Manager Sound Scoped Timer Allocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDeallocate(
	TEXT("log.manager.sound.scopedtimer.deallocate"),
	0,
	TEXT("Log Manager Sound Scoped Timer Deallocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDeallocateObject(
	TEXT("log.manager.sound.scopedtimer.deallocateobject"),
	0,
	TEXT("Log Manager Sound Scoped Timer Deallocate Object."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerSpawn(
	TEXT("log.manager.sound.scopedtimer.spawn"),
	0,
	TEXT("Log Manager Sound Scoped Timer Spawn."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerSoundScopedTimerDestroy(
	TEXT("log.manager.sound.scopedtimer.destroy"),
	0, 
	TEXT("Log Manager Sound Scoped Timer Destroy."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundTransactions, "Log Manager Sound Transactions");
	// Scoped Timer
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimer, "Log Manager Sound Scoped Timer");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerCreatePool, "Log Manager Sound Scoped Timer Create Pool");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerUpdate, "Log Manager Sound Scoped Timer Update");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerUpdateObject, "Log Manager Sound Scoped Timer Update Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerAllocate, "Log Manager Sound Scoped Allocate");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerAllocateObject, "Log Manager Sound Scoped Allocate Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerDeallocate, "Log Manager Sound Scoped Timer Deallocate");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerDeallocateObject, "Log Manager Sound Scoped Timer Deallocate Object");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerSpawn, "Log Manager Sound Scoped Timer Spawn");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerDestroy, "Log Manager Sound Scoped Timer Destroy");


	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundTransactions, CsCVarLogManagerSoundTransactions);
		// Scoped Timer
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimer, CsCVarLogManagerSoundScopedTimer);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerCreatePool, CsCVarLogManagerSoundScopedTimerCreatePool);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerUpdate, CsCVarLogManagerSoundScopedTimerUpdate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerUpdateObject, CsCVarLogManagerSoundScopedTimerUpdateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerAllocate, CsCVarLogManagerSoundScopedTimerAllocate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerAllocateObject, CsCVarLogManagerSoundScopedTimerAllocateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDeallocate, CsCVarLogManagerSoundScopedTimerDeallocate);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDeallocateObject, CsCVarLogManagerSoundScopedTimerDeallocateObject);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerSpawn, CsCVarLogManagerSoundScopedTimerSpawn);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDestroy, CsCVarLogManagerSoundScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerSound, "Manager Sound");

	namespace Map
	{
		extern CSCORE_API CS_ADD_TO_CVAR_MAP(ManagerSound, CsCVarLogManagerSoundScopedTimer);
	}
}

#pragma endregion ScopedGroup