// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSSKELETALMESH_API TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChange;
extern CSSKELETALMESH_API TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeSet;
extern CSSKELETALMESH_API TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeClear;
extern CSSKELETALMESH_API TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeCounter;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSSKELETALMESH_API const Type LogSkeletalMeshActorPooledChange;
	extern CSSKELETALMESH_API const Type LogSkeletalMeshActorPooledChangeSet;
	extern CSSKELETALMESH_API const Type LogSkeletalMeshActorPooledChangeClear;
	extern CSSKELETALMESH_API const Type LogSkeletalMeshActorPooledChangeCounter;

	namespace Map
	{
		extern CSSKELETALMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChange);
		extern CSSKELETALMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeSet);
		extern CSSKELETALMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeClear);
		extern CSSKELETALMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//extern CSSKELETALMESH_API const Type SkeletalMeshActor;

	namespace Map
	{
		//extern CSSKELETALMESH_API CS_DECLARE_ADD_TO_CVAR_MAP(SkeletalMeshActor);
	}
}

#pragma endregion ScopedGroup