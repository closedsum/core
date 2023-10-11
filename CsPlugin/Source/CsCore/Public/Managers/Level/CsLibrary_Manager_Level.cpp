// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/CsLibrary_Manager_Level.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Level/CsManager_Level.h"
// Settings
#include "Managers/Level/CsSettings_Manager_Level.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
// Managers
#include "Managers/Singleton/CsGetManagerSingleton.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsLevel
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NManager::FLibrary, GetContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NManager::FLibrary, GetSafeContextRoot);
					CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(ContextObject, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}

			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(ContextObject, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}

			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsLevel::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Level* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		    = GetContextRootChecked(Context, ContextObject);
			UCsManager_Level* Manager_Level = UCsManager_Level::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Level)
			return Manager_Level;
		}

		UCsManager_Level* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Level* Manager_Level = UCsManager_Level::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Level)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Level."), *Context));
			}
			return Manager_Level;
		}

		UCsManager_Level* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			OutSuccess = false;

			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Level* Manager_Level = UCsManager_Level::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Level)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Level."), *Context));
			}

			OutSuccess = true;

			return Manager_Level;
		}

		UCsManager_Level* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsLevel::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Class
		#pragma region

		TSubclassOf<UCsManager_Level> FLibrary::GetClassChecked(const FString& Context)
		{
			const FCsSettings_Manager_Level& Settings = FCsSettings_Manager_Level::Get();

			return TSubclassOf<UCsManager_Level>(Settings.LoadClassChecked(Context));
		}

		#pragma endregion Class

		// Persistent Level
		#pragma region

		bool FLibrary::HasFinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextRoot)
		{
			return GetChecked(Context, ContextRoot)->HasFinishedLoadingPersistentLevel();
		}

		void FLibrary::Check_FinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextRoot)
		{
			GetChecked(Context, ContextRoot)->Check_FinishedLoadingPersistentLevel();
		}

		void FLibrary::Check_FinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextRoot, const FString& MapPackageName)
		{
			GetChecked(Context, ContextRoot)->Check_FinishedLoadingPersistentLevel(MapPackageName);
		}

		#pragma endregion Persistent Level

		// Change Map
		#pragma region

		bool FLibrary::HasChangeMapCompletedChecked(const FString& Context, const UObject* ContextRoot)
		{
			return GetChecked(Context, ContextRoot)->HasChangeMapCompleted();
		}

		bool FLibrary::SafeHasChangeMapCompleted(const FString& Context, const UObject* ContextRoot, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Level* Manager_Level = GetSafe(Context, ContextRoot, Log))
			{
				return Manager_Level->HasChangeMapCompleted();
			}
			return false;
		}

		bool FLibrary::SafeHasChangeMapCompleted(const FString& Context, const UObject* ContextRoot, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			OutSuccess = false;

			if (UCsManager_Level* Manager_Level = GetSafe(Context, ContextRoot, Log))
			{
				OutSuccess = true;
				return Manager_Level->HasChangeMapCompleted();
			}
			return false;
		}

		#define ParamsType NCsLevel::NManager::NChangeMap::FParams

		void FLibrary::ChangeMapChecked(const FString& Context, const UObject* ContextRoot, const ParamsType& Params)
		{
			GetChecked(Context, ContextRoot)->ChangeMap(Params);
		}

		bool FLibrary::SafeChangeMap(const FString& Context, const UObject* ContextRoot, const ParamsType& Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Level* Manager_Level = GetSafe(Context, ContextRoot, Log))
			{
				CS_IS_VALID(Params)

				Manager_Level->ChangeMap(Params);
				return true;
			}
			return false;
		}

		#undef ParamsType

		#pragma endregion Change Map

		#if WITH_EDITOR

		bool FLibrary::HasFinishedDestroyingOtherPIEWorld(const FString& Context, UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->HasFinishedDestroyingOtherPIEWorld();
		}

		void FLibrary::DestroyOtherPIEWorldChecked(const FString& Context, UObject* ContextObject, const FString& URL)
		{
			GetChecked(Context, ContextObject)->DestroyOtherPIEWorld(URL);
		}

		#endif // #if WITH_EDITOR
	}
}