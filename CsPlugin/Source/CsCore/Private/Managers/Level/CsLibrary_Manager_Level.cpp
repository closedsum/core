// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Level/CsLibrary_Manager_Level.h"
#include "CsCore.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Level/CsManager_Level.h"
// Settings
#include "Managers/Level/CsSettings_Manager_Level.h"
// Level
#include "Engine/LevelStreaming.h"


#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
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
		
		using LogClassType = FCsLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsLevel::NManager::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsLevel::NManager::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		using ParamsType = NCsLevel::NManager::NChangeMap::FParams;
		using OnChangeMapStartEventType = NCsLevel::NManager::FChangeMap_OnStart;
		using OnChangeMapCompleteEventType = NCsLevel::NManager::FChangeMap_OnComplete;
		using OnLevelLoadedEventType = NCsLevel::NManager::NLevel::NStreaming::FOnLoaded;
		using OnLevelUnloadedEventType = NCsLevel::NManager::NLevel::NStreaming::FOnUnloaded;
		using OnLevelShownEventType = NCsLevel::NManager::NLevel::NStreaming::FOnShown;
		using OnLevelHiddenEventType = NCsLevel::NManager::NLevel::NStreaming::FOnHidden;

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(ContextObject, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}
			return CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(ContextObject, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}
			return CsGameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			SET_CONTEXT(GetSafeContextRoot);

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Level* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
		#if WITH_EDITOR
			UObject* ContextRoot		    = GetContextRootChecked(Context, ContextObject);
			UCsManager_Level* Manager_Level = UCsManager_Level::Get(ContextRoot);

			CS_IS_PENDING_KILL_CHECKED(Manager_Level)
			return Manager_Level;
		#else
			return UCsManager_Level::Get(nullptr);
		#endif // #if WITH_EDITOR
		}

		UCsManager_Level* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Level* Manager_Level = UCsManager_Level::GetSafe(Context, ContextRoot, Log);

			if (!CsObjectLibrary::IsValidObject(Manager_Level))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Level."), *Context));
			}
			return Manager_Level;
		}

		UCsManager_Level* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Level* Manager_Level = UCsManager_Level::GetSafe(Context, ContextRoot, Log);

			if (!CsObjectLibrary::IsValidObject(Manager_Level))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Level."), *Context));
			}

			OutSuccess = true;

			return Manager_Level;
		}

		UCsManager_Level* FLibrary::GetSafe(const UObject* ContextObject)
		{
			SET_CONTEXT(GetSafe);

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

		bool FLibrary::HasFinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->HasFinishedLoadingPersistentLevel();
		}

		void FLibrary::Check_FinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->Check_FinishedLoadingPersistentLevel();
		}

		void FLibrary::Check_FinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextObject, const FString& MapPackageName)
		{
			GetChecked(Context, ContextObject)->Check_FinishedLoadingPersistentLevel(MapPackageName);
		}

		void FLibrary::ClearCheck_FinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->ClearCheck_Check_FinishedLoadingPersistentLevel();
		}

		#pragma endregion Persistent Level

		// Change Map
		#pragma region

		bool FLibrary::HasChangeMapCompletedChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->HasChangeMapCompleted();
		}

		bool FLibrary::SafeHasChangeMapCompleted(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Level* Manager_Level = GetSafe(Context, ContextObject, Log))
			{
				return Manager_Level->HasChangeMapCompleted();
			}
			return false;
		}

		bool FLibrary::SafeHasChangeMapCompleted(const FString& Context, const UObject* ContextObject, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			if (UCsManager_Level* Manager_Level = GetSafe(Context, ContextObject, Log))
			{
				OutSuccess = true;
				return Manager_Level->HasChangeMapCompleted();
			}
			return false;
		}

		void FLibrary::ChangeMapChecked(const FString& Context, const UObject* ContextObject, const ParamsType& Params)
		{
			GetChecked(Context, ContextObject)->ChangeMap(Params);
		}

		bool FLibrary::SafeChangeMap(const FString& Context, const UObject* ContextObject, const ParamsType& Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Level* Manager_Level = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_VALID(Params)

				Manager_Level->ChangeMap(Params);
				return true;
			}
			return false;
		}

		OnChangeMapStartEventType& FLibrary::GetChangeMap_OnStart_EventChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetChangeMap_OnStart_Event();
		}

		OnChangeMapCompleteEventType& FLibrary::GetChangeMap_OnComplete_EventChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetChangeMap_OnComplete_Event();
		}

		#pragma endregion Change Map

		// Streaming
		#pragma region

		OnLevelLoadedEventType& FLibrary::GetLevel_Streaming_OnLoaded_EventChecked(const FString& Context, UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetLevel_Streaming_OnLoaded_Event();
		}

		void FLibrary::BroadcastChecked_Level_Streaming_OnLoaded(const FString& Context, UObject* ContextObject, ULevelStreaming* Level)
		{
			CS_IS_PENDING_KILL_CHECKED(Level)

			GetChecked(Context, ContextObject)->Broadcast_Level_Streaming_OnLoaded(Level);
		}

		OnLevelUnloadedEventType& FLibrary::GetLevel_Streaming_OnUnloaded_EventChecked(const FString& Context, UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetLevel_Streaming_OnUnloaded_Event();
		}

		void FLibrary::BroadcastChecked_Level_Streaming_OnUnloaded(const FString& Context, UObject* ContextObject, ULevelStreaming* Level)
		{
			CS_IS_PENDING_KILL_CHECKED(Level)

			GetChecked(Context, ContextObject)->Broadcast_Level_Streaming_OnUnloaded(Level);
		}

		OnLevelShownEventType& FLibrary::GetLevel_Streaming_OnShown_EventChecked(const FString& Context, UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetLevel_Streaming_OnShown_Event();
		}

		void FLibrary::BroadcastChecked_Level_Streaming_OnShown(const FString& Context, UObject* ContextObject, ULevelStreaming* Level)
		{
			CS_IS_PENDING_KILL_CHECKED(Level)

			GetChecked(Context, ContextObject)->Broadcast_Level_Streaming_OnShown(Level);
		}

		OnLevelHiddenEventType& FLibrary::GetLevel_Streaming_OnHidden_EventChecked(const FString& Context, UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetLevel_Streaming_OnHidden_Event();
		}

		void FLibrary::BroadcastChecked_Level_Streaming_OnHidden(const FString& Context, UObject* ContextObject, ULevelStreaming* Level)
		{
			CS_IS_PENDING_KILL_CHECKED(Level)

			GetChecked(Context, ContextObject)->Broadcast_Level_Streaming_OnHidden(Level);
		}

		#pragma endregion Streaming

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

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}