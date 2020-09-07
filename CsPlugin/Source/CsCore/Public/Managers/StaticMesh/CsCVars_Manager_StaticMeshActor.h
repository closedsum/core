// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorTransactions;
// Scoped Timers
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerCreatePool;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerUpdate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerUpdateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerAllocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerAllocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDeallocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDeallocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerSpawn;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerStaticMeshActorTransactions;
	// Scoped Timer
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimer;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerCreatePool;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerUpdate;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerUpdateObject;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerAllocate;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerAllocateObject;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerDeallocate;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerDeallocateObject;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerSpawn;
	extern CSCORE_API const Type LogManagerStaticMeshActorScopedTimerDestroy;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorTransactions);
		// Scoped Timer
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerCreatePool);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerUpdate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerUpdateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerAllocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerAllocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDeallocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDeallocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerSpawn);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerStaticMeshActor;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerStaticMeshActor);
	}
}

#pragma endregion ScopedGroup