// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorTransactions;
// Scoped Timers
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimer;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerCreatePool;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerUpdate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerUpdateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerAllocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerAllocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerDeallocate;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerDeallocateObject;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerSpawn;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSkeletalMeshActorScopedTimerDestroy;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerSkeletalMeshActorTransactions;
	// Scoped Timer
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimer;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerCreatePool;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerUpdate;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerUpdateObject;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerAllocate;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerAllocateObject;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerDeallocate;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerDeallocateObject;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerSpawn;
	extern CSCORE_API const Type LogManagerSkeletalMeshActorScopedTimerDestroy;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorTransactions);
		// Scoped Timer
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimer);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerCreatePool);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerUpdate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerUpdateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerAllocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerAllocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerDeallocate);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerDeallocateObject);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerSpawn);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerSkeletalMeshActorScopedTimerDestroy);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerSkeletalMeshActor;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerSkeletalMeshActor);
	}
}

#pragma endregion ScopedGroup