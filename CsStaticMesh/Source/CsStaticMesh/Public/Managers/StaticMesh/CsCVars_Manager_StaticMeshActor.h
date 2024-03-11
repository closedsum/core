// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorTransactions;
// Scoped Timers
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimer;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerCreatePool;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerUpdate;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerUpdateObject;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerAllocate;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerAllocateObject;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDeallocate;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDeallocateObject;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerSpawn;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogManagerStaticMeshActorScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorTransactions;
	// Scoped Timer
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimer;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerCreatePool;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerUpdate;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerUpdateObject;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerAllocate;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerAllocateObject;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerDeallocate;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerDeallocateObject;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerSpawn;
	extern CSSTATICMESH_API const Type LogManagerStaticMeshActorScopedTimerDestroy;

	namespace Map
	{
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorTransactions);
		// Scoped Timer
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimer);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerCreatePool);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerUpdate);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerUpdateObject);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerAllocate);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerAllocateObject);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDeallocate);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDeallocateObject);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerSpawn);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerStaticMeshActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSSTATICMESH_API const Type ManagerStaticMeshActor;

	namespace Map
	{
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerStaticMeshActor);
	}
}

#pragma endregion ScopedGroup