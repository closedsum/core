// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Spawner/Script/CsScriptLibrary_Manager_Spawner.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Spawner/CsLibrary_Manager_Spawner.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_Spawner)

// Cached
#pragma region

namespace NCsScriptLibraryManagerSpawner
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Spawner, Get);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Spawner::UCsScriptLibrary_Manager_Spawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerSpawner::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerSpawner::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Get
#pragma region

UCsManager_Spawner* UCsScriptLibrary_Manager_Spawner::Get(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(Get);

	return CsSpawnerManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT