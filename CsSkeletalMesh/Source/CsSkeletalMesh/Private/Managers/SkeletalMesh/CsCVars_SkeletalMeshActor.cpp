// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/SkeletalMesh/CsCVars_SkeletalMeshActor.h"

TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChange(
	TEXT("log.skeletalmeshactor.pooled.change"),
	0,
	TEXT("Log SkeletalMeshActor Pooled Changes (Preserved between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeSet(
	TEXT("log.skeletalmeshactor.pooled.change.set"),
	0,
	TEXT("Log SkeletalMeshActor Pooled Changes Set (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeClear(
	TEXT("log.skeletalmeshactor.pooled.change.clear"),
	0,
	TEXT("Log SkeletalMeshActor Pooled Changes Clear (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeCounter(
	TEXT("log.skeletalmeshactor.pooled.change.counter"),
	0,
	TEXT("Log SkeletalMeshActor Pooled Changes Counter (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSkeletalMeshActorPooledChange, "Log SkeletalMeshActor Pooled Changes (Preserved between Allocate and Deallocate)");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSkeletalMeshActorPooledChangeSet, "Log SkeletalMeshActor Pooled Changes Set (Between Allocate and Deallocate)");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSkeletalMeshActorPooledChangeClear, "Log SkeletalMeshActor Pooled Changes Clear (Between Allocate and Deallocate)");
	CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSkeletalMeshActorPooledChangeCounter, "Log SkeletalMeshActor Pooled Changes Counter (Between Allocate and Deallocate)");

	namespace Map
	{
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChange, CsCVarLogSkeletalMeshActorPooledChange);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeSet, CsCVarLogSkeletalMeshActorPooledChangeSet);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeClear, CsCVarLogSkeletalMeshActorPooledChangeClear);
		CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeCounter, CsCVarLogSkeletalMeshActorPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//CSSKELETALMESH_API CS_CREATE_ENUM_STRUCT_CUSTOM(SkeletalMeshActor, "SkeletalMeshActor");

	namespace Map
	{
		//extern CSSKELETALMESH_API CS_ADD_TO_CVAR_MAP(SkeletalMeshActor, CsCVarLogSkeletalMeshActorScopedTimer);
	}
}

#pragma endregion ScopedGroup