// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Performance/CsLibrary_Manager_Performance.h"

// Types
#include "CsMacro_Misc.h"
// Managers
#include "Managers/Performance/CsManager_Performance.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Managers/Performance/CsSettings_Manager_Performance.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_2(NCsPerformance, NManager, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsPerformance::NManager::FLibrary, GetSafeContextRoot)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsPerformance::NManager::FLibrary, GetSafe)
CS_END_CACHED_FUNCTION_NAME_NESTED_2

#pragma endregion Cached

namespace NCsPerformance
{
	namespace NManager
	{
		using LogClassType = NCsPerformance::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			return CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			return CsGameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafeContextRoot);

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Performance* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Performance* Manager_Performance = UCsManager_Performance::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Performance)
			return Manager_Performance;
		}

		UCsManager_Performance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Performance* Manager_Performance = UCsManager_Performance::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Performance)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Performance."), *Context));
				return nullptr;
			}
			return Manager_Performance;
		}

		UCsManager_Performance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Performance* Manager_Performance = UCsManager_Performance::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Performance)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Performance."), *Context));
				return nullptr;
			}

			OutSuccess = true;
			return Manager_Performance;
		}

		UCsManager_Performance* FLibrary::GetSafe(const UObject* ContextObject)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafe);

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Class
		#pragma region

		TSubclassOf<UCsManager_Performance> FLibrary::GetClassChecked(const FString& Context)
		{
			const FCsSettings_Manager_Performance& Settings = FCsSettings_Manager_Performance::Get();

			return TSubclassOf<UCsManager_Performance>(Settings.LoadClassChecked(Context));
		}

		#pragma endregion Class

		void FLibrary::CreatePerformanceWidgetChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->CreatePerformanceWidget();
		}

		void FLibrary::ConditionalCreatePerformanceWidgetChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->ConditionalCreatePerformanceWidget();
		}
	}
}