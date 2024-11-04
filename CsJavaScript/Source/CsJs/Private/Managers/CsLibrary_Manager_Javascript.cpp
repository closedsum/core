// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/CsLibrary_Manager_Javascript.h"

// Types
#include "CsMacro_Misc.h"
// Managers
#include "Managers/CsManager_Javascript.h"
// Library
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
// Game
#include "Engine/GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsJs
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NManager::FLibrary, GetSafe);
				}
			}
		}

		using LogClassType = NCsJs::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			// TODO: FUTURE: Some sort of flag to properly indicate getting GEngine as ContextRoot
			if (ContextObject == GEngine)
				return GEngine;
			return CsGameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			// TODO: FUTURE: Some sort of flag to properly indicate getting GEngine as ContextRoot
			if (ContextObject == GEngine)
				return GEngine;
			return CsGameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsJs::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		UObject* FLibrary::GetEngineContextRoot()
		{
			return GEngine;
		}

		// Get
		#pragma region

		UCsManager_Javascript* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot					  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Javascript* Manager_Javascript = UCsManager_Javascript::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Javascript)
			return Manager_Javascript;
		}

		UCsManager_Javascript* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			UCsManager_Javascript* Manager_Javascript = UCsManager_Javascript::GetSafe(Context, ContextRoot, Log);
		#else
			UCsManager_Javascript* Manager_Javascript = UCsManager_Javascript::Get(ContextRoot);
		#endif // #if WITH_EDITOR
			return Manager_Javascript;
		}

		UCsManager_Javascript* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsJs::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get
	}
}