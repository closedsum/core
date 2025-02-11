// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Achievement/CsLibrary_Manager_Achievement.h"
#include "CsPlatformServices.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Achievement/CsManager_Achievement.h"
// Game
#include "Engine/GameInstance.h"

using LogClassType = NCsPlatformServices::FLog;

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

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* ContextObject)
		{
			return CsGameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			return CsGameInstanceLibrary::GetSafe(Context, ContextObject, Log);
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

		UCsManager_Achievement* FLibrary::GetSafe(const FString& Context, UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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

		void FLibrary::CompleteChecked(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement)
		{
			GetChecked(Context, ContextObject)->Complete(Achievement);
		}

		void FLibrary::SafeComplete(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				Manager_Achievement->SafeComplete(Achievement);
			}
		}

		bool FLibrary::IsCompletedChecked(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement)
		{
			return GetChecked(Context, ContextObject)->IsCompleted(Achievement);
		}

		bool FLibrary::IsSafeCompleted(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				return Manager_Achievement->IsSafeCompleted(Achievement);
			}
			return false;
		}

		int32 FLibrary::GetNumCompletedChecked(const FString& Context, UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetNumCompleted();
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

		// Reset
		#pragma region

		void FLibrary::ResetChecked(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, const float& Percent /*=0.0f*/)
		{
			GetChecked(Context, ContextObject)->Reset(Achievement, Percent);
		}

		void FLibrary::SafeReset(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, const float& Percent /*=0.0f*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				typedef NCsAchievement::FValue ValueType;

				ValueType Value;
				Value.SetPercent(Percent);

				Manager_Achievement->SafeReset(Achievement, Value);
			}
		}

		void FLibrary::ResetAllChecked(const FString& Context, UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->ResetAll();
		}

		void FLibrary::SafeResetAll(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*= FCsLog::Warning*/)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				Manager_Achievement->ResetAll();
			}
		}

		#pragma endregion Reset

		// Progress
		#pragma region

		float FLibrary::GetProgressChecked(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement)
		{
			return GetChecked(Context, ContextObject)->GetProgress(Achievement);
		}

		float FLibrary::GetSafeProgress(const FString& Context, UObject* ContextObject, const FECsAchievement& Achievement, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				return Manager_Achievement->GetSafeProgress(Achievement);
			}
			return 0.0f;
		}

		float FLibrary::GetTotalProgressChecked(const FString& Context, UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetTotalProgress();
		}

		float FLibrary::GetSafeTotalProgress(const FString& Context, UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Achievement* Manager_Achievement = GetSafe(Context, ContextObject, Log))
			{
				return Manager_Achievement->GetTotalProgress();
			}
			return 0.0f;
		}

		#pragma endregion Progress
	}
}