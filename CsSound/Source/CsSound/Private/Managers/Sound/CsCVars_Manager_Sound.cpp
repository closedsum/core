// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundTransactions, "Log Manager Sound Transactions");
	// Scoped Timer
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimer, "Log Manager Sound Scoped Timer");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerCreatePool, "Log Manager Sound Scoped Timer Create Pool");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerUpdate, "Log Manager Sound Scoped Timer Update");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerUpdateObject, "Log Manager Sound Scoped Timer Update Object");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerAllocate, "Log Manager Sound Scoped Allocate");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerAllocateObject, "Log Manager Sound Scoped Allocate Object");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerDeallocate, "Log Manager Sound Scoped Timer Deallocate");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerDeallocateObject, "Log Manager Sound Scoped Timer Deallocate Object");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerSpawn, "Log Manager Sound Scoped Timer Spawn");
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerSoundScopedTimerDestroy, "Log Manager Sound Scoped Timer Destroy");


	namespace Map
	{
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundTransactions, CsCVarLogManagerSoundTransactions);
		// Scoped Timer
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimer, CsCVarLogManagerSoundScopedTimer);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerCreatePool, CsCVarLogManagerSoundScopedTimerCreatePool);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerUpdate, CsCVarLogManagerSoundScopedTimerUpdate);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerUpdateObject, CsCVarLogManagerSoundScopedTimerUpdateObject);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerAllocate, CsCVarLogManagerSoundScopedTimerAllocate);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerAllocateObject, CsCVarLogManagerSoundScopedTimerAllocateObject);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDeallocate, CsCVarLogManagerSoundScopedTimerDeallocate);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDeallocateObject, CsCVarLogManagerSoundScopedTimerDeallocateObject);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerSpawn, CsCVarLogManagerSoundScopedTimerSpawn);
		CSSOUND_API CS_ADD_TO_CVAR_MAP(LogManagerSoundScopedTimerDestroy, CsCVarLogManagerSoundScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSSOUND_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerSound, "Manager Sound");

	namespace Map
	{
		extern CSSOUND_API CS_ADD_TO_CVAR_MAP(ManagerSound, CsCVarLogManagerSoundScopedTimer);
	}
}

#pragma endregion ScopedGroup