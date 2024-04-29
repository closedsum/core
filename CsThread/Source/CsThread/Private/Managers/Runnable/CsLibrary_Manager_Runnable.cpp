// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Runnable/CsLibrary_Manager_Runnable.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Runnable/CsManager_Runnable.h"
// Game
#include "Engine/GameInstance.h"

namespace NCsRunnable
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsRunnable::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsRunnable::NManager::FLibrary, GetSafe);
				}
			}
		}

		#define LogLevel void(*Log)(const FString&) /*=&NCsThread::FLog::Warning*/
		#define GameInstanceLibrary NCsGameInstance::FLibrary

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* ContextObject)
		{
			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* ContextObject, LogLevel)
		{
			return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* ContextObject)
		{
			using namespace NCsRunnable::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Runnable* FLibrary::GetChecked(const FString& Context, UObject* ContextObject)
		{
			UObject* ContextRoot				  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Runnable)
			return Manager_Runnable;
		}

		UCsManager_Runnable* FLibrary::GetSafe(const FString& Context, UObject* ContextObject, LogLevel)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Runnable* Manager_Runnable = UCsManager_Runnable::Get(ContextRoot);

			if (!Manager_Runnable)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Runnable."), *Context));
			}
			return Manager_Runnable;
		}

		UCsManager_Runnable* FLibrary::GetSafe(UObject* ContextObject)
		{
			using namespace NCsRunnable::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		#undef LogLevel
		#undef GameInstanceLibrary
	}
}