// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Performance/CsLibrary_Manager_Performance.h"

// Types
#include "Types/CsTypes_Macro.h"
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

namespace NCsPerformance
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPerformance::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPerformance::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		#define GameInstanceLibrary NCsGameInstance::FLibrary

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void (*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsPerformance::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#undef GameInstanceLibrary

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

		UCsManager_Performance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsUI::FLog::Warning*/)
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

		UCsManager_Performance* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) /*= &NCsUI::FLog::Warning*/)
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
			using namespace NCsPerformance::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

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