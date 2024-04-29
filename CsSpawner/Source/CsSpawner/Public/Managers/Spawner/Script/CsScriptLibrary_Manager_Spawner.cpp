// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Spawner/Script/CsScriptLibrary_Manager_Spawner.h"
#include "CsSpawner.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Spawner/CsLibrary_Manager_Spawner.h"

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

#define SpawnerManagerLibrary NCsSpawner::NManager::FLibrary

// Get
#pragma region

UCsManager_Spawner* UCsScriptLibrary_Manager_Spawner::Get(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerSpawner::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return SpawnerManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

#pragma endregion Get

#undef SpawnerManagerLibrary