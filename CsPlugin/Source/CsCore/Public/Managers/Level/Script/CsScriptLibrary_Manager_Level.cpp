// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/Script/CsScriptLibrary_Manager_Level.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Managers/Level/CsLibrary_Manager_Level.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerLevel
{
	namespace NCached
	{
		namespace Str
		{
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_Level, Get);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_Level::UCsScriptLibrary_Manager_Level(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define LevelManagerLibrary NCsLevel::NManager::FLibrary
// Get
#pragma region

UCsManager_Level* UCsScriptLibrary_Manager_Level::Get(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryManagerLevel::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Get : Context;

	return LevelManagerLibrary::GetSafe(Ctxt, WorldContextObject);
}

#pragma endregion Get

#undef LevelManagerLibrary