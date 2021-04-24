// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Achievement/CsLibrary_Manager_Achievement.h"
#include "CsPlatformServices.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Achievement/CsManager_Achievement.h"
// Game
#include "Engine/GameInstance.h"

namespace NCsAchievement
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsAchievement::NManager::FLibrary, GetSafeContextRoot);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* ContextObject)
		{
			using namespace NCsAchievement::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Achievement* FLibrary::GetChecked(const FString& Context, UObject* ContextObject)
		{
			UObject* ContextRoot						= GetContextRootChecked(Context, ContextObject);
			UCsManager_Achievement* Manager_Achievement = UCsManager_Achievement::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Achievement)
			return Manager_Achievement;
		}

		UCsManager_Achievement* FLibrary::GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Achievement* Manager_Achievement = UCsManager_Achievement::Get(ContextRoot);

			if (!Manager_Achievement)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Achievement."), *Context));
			}
			return Manager_Achievement;
		}

		#pragma endregion Get

		// Complete
		#pragma region

		void FLibrary::SafeComplete(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				Manager_Achievement->SafeComplete(Achievement);
			}
		}

		bool FLibrary::SafeIsCompleted(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				return Manager_Achievement->IsSafeCompleted(Achievement);
			}
			return false;
		}

		int32 FLibrary::GetSafeNumCompleted(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /* &FCsLog::Warning*/)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				return Manager_Achievement->GetNumCompleted();
			}
			return 0;
		}

		#pragma endregion Complete
	}
}