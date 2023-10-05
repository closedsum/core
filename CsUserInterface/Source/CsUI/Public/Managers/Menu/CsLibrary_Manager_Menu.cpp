// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Menu/CsLibrary_Manager_Menu.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Menu/CsManager_Menu.h"
// Settings
#include "Managers/Menu/CsSettings_Manager_Menu.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsMenu
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMenu::NManager::FLibrary, GetContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMenu::NManager::FLibrary, GetSafeContextRoot);
					CSUI_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMenu::NManager::FLibrary, GetSafe);
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

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsMenu::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#undef GameInstanceLibrary

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Menu* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Menu* Manager_Menu = UCsManager_Menu::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Menu)
			return Manager_Menu;
		}

		UCsManager_Menu* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Menu* Manager_Menu = UCsManager_Menu::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Menu)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Menu."), *Context));
				return nullptr;
			}
			return Manager_Menu;
		}

		UCsManager_Menu* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			OutSuccess = false;

			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Menu* Manager_Menu = UCsManager_Menu::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Menu)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Menu."), *Context));
				return nullptr;
			}

			OutSuccess = true;
			return Manager_Menu;
		}

		UCsManager_Menu* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsMenu::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Class
		#pragma region

		TSubclassOf<UCsManager_Menu> FLibrary::GetClassChecked(const FString& Context)
		{
			const FCsSettings_Manager_Menu& Settings = FCsSettings_Manager_Menu::Get();

			return TSubclassOf<UCsManager_Menu>(Settings.LoadClassChecked(Context));
		}

		#pragma endregion Class
	}
}