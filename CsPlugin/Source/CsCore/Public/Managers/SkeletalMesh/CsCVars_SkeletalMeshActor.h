// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeSet;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeClear;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogSkeletalMeshActorPooledChangeCounter;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogSkeletalMeshActorPooledChange;
	extern CSCORE_API const Type LogSkeletalMeshActorPooledChangeSet;
	extern CSCORE_API const Type LogSkeletalMeshActorPooledChangeClear;
	extern CSCORE_API const Type LogSkeletalMeshActorPooledChangeCounter;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeSet);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeClear);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSkeletalMeshActorPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//extern CSCORE_API const Type SkeletalMeshActor;

	namespace Map
	{
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(SkeletalMeshActor);
	}
}

#pragma endregion ScopedGroup