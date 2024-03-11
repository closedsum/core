// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChange;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeSet;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeClear;
extern CSSTATICMESH_API TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeCounter;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSSTATICMESH_API const Type LogStaticMeshActorPooledChange;
	extern CSSTATICMESH_API const Type LogStaticMeshActorPooledChangeSet;
	extern CSSTATICMESH_API const Type LogStaticMeshActorPooledChangeClear;
	extern CSSTATICMESH_API const Type LogStaticMeshActorPooledChangeCounter;

	namespace Map
	{
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChange);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeSet);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeClear);
		extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//extern CSSTATICMESH_API const Type StaticMeshActor;

	namespace Map
	{
		//extern CSSTATICMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(StaticMeshActor);
	}
}

#pragma endregion ScopedGroup