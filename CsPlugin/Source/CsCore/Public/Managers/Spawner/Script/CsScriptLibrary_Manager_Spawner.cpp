// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Spawner/Script/CsScriptLibrary_Manager_Spawner.h"
#include "CsCore.h"

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

// Get
#pragma region

UCsManager_Spawner* UCsScriptLibrary_Manager_Spawner::Get(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerSpawner::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	typedef NCsSpawner::NManager::FLibrary SpawnerManagerLibrary;

	return SpawnerManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

#pragma endregion Get