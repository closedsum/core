// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeSet;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeClear;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogStaticMeshActorPooledChangeCounter;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogStaticMeshActorPooledChange;
	extern CSCORE_API const Type LogStaticMeshActorPooledChangeSet;
	extern CSCORE_API const Type LogStaticMeshActorPooledChangeClear;
	extern CSCORE_API const Type LogStaticMeshActorPooledChangeCounter;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeSet);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeClear);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogStaticMeshActorPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//extern CSCORE_API const Type StaticMeshActor;

	namespace Map
	{
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(StaticMeshActor);
	}
}

#pragma endregion ScopedGroup