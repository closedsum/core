// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSkeletalMeshActorPooledChange, "Log SkeletalMeshActor Pooled Changes (Preserved between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSkeletalMeshActorPooledChangeSet, "Log SkeletalMeshActor Pooled Changes Set (Between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSkeletalMeshActorPooledChangeClear, "Log SkeletalMeshActor Pooled Changes Clear (Between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSkeletalMeshActorPooledChangeCounter, "Log SkeletalMeshActor Pooled Changes Counter (Between Allocate and Deallocate)");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChange, CsCVarLogSkeletalMeshActorPooledChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeSet, CsCVarLogSkeletalMeshActorPooledChangeSet);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeClear, CsCVarLogSkeletalMeshActorPooledChangeClear);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeCounter, CsCVarLogSkeletalMeshActorPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(SkeletalMeshActor, "SkeletalMeshActor");

	namespace Map
	{
		//extern CSCORE_API CS_ADD_TO_CVAR_MAP(SkeletalMeshActor, CsCVarLogSkeletalMeshActorScopedTimer);
	}
}

#pragma endregion ScopedGroup