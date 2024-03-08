// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/CsCVars_StaticMeshActor.h"

TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChange(
	TEXT("log.staticmeshactor.pooled.change"),
	0,
	TEXT("Log StaticMeshActor Pooled Changes (Preserved between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeSet(
	TEXT("log.staticmeshactor.pooled.change.set"),
	0,
	TEXT("Log StaticMeshActor Pooled Changes Set (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeClear(
	TEXT("log.staticmeshactor.pooled.change.clear"),
	0,
	TEXT("Log StaticMeshActor Pooled Changes Clear (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeCounter(
	TEXT("log.staticmeshactor.pooled.change.counter"),
	0,
	TEXT("Log StaticMeshActor Pooled Changes Counter (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogStaticMeshActorPooledChange, "Log StaticMeshActor Pooled Changes (Preserved between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogStaticMeshActorPooledChangeSet, "Log StaticMeshActor Pooled Changes Set (Between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogStaticMeshActorPooledChangeClear, "Log StaticMeshActor Pooled Changes Clear (Between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogStaticMeshActorPooledChangeCounter, "Log StaticMeshActor Pooled Changes Counter (Between Allocate and Deallocate)");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChange, CsCVarLogStaticMeshActorPooledChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeSet, CsCVarLogStaticMeshActorPooledChangeSet);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeClear, CsCVarLogStaticMeshActorPooledChangeClear);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeCounter, CsCVarLogStaticMeshActorPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(StaticMeshActor, "StaticMeshActor");

	namespace Map
	{
		//extern CSCORE_API CS_ADD_TO_CVAR_MAP(StaticMeshActor, CsCVarLogStaticMeshActorScopedTimer);
	}
}

#pragma endregion ScopedGroup