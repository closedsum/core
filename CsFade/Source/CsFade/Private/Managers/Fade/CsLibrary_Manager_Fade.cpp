// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/CsLibrary_Manager_Fade.h"

// Types
#include "CsMacro_Misc.h"
// Managers
#include "Managers/Fade/CsManager_Fade.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Managers/Fade/CsSettings_Manager_Fade.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsFade
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFade::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFade::NManager::FLibrary, GetSafe);
				}
			}
		}

		#define LogWarning void(*Log)(const FString&) /*=&NCsFade::FLog::Warning*/

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		#define GameInstanceLibrary NCsGameInstance::FLibrary

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogWarning)
		{
			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsFade::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#undef GameInstanceLibrary

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Fade* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Fade* Manager_Fade = UCsManager_Fade::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Fade)
			return Manager_Fade;
		}

		UCsManager_Fade* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, LogWarning)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Fade* Manager_Fade = UCsManager_Fade::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Fade)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Fade."), *Context));
				return nullptr;
			}
			return Manager_Fade;
		}

		UCsManager_Fade* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, LogWarning)
		{
			OutSuccess = false;

			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Fade* Manager_Fade = UCsManager_Fade::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Fade)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Fade."), *Context));
				return nullptr;
			}

			OutSuccess = true;
			return Manager_Fade;
		}

		UCsManager_Fade* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsFade::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Class
		#pragma region

		TSubclassOf<UCsManager_Fade> FLibrary::GetClassChecked(const FString& Context)
		{
			const FCsSettings_Manager_Fade& Settings = FCsSettings_Manager_Fade::Get();

			return TSubclassOf<UCsManager_Fade>(Settings.LoadClassChecked(Context));
		}

		#pragma endregion Class

		void FLibrary::CreateFadeWidget(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->CreateFadeWidget();
		}

		#define ParamsType NCsFade::FParams

		void FLibrary::FadeChecked(const FString& Context, const UObject* ContextObject, const ParamsType& Params)
		{
			GetChecked(Context, ContextObject)->Fade(Params);
		}

		bool FLibrary::SafeFade(const UObject* ContextObject, const ParamsType& Params)
		{

		#if WITH_EDITOR
			if (UCsManager_Fade* Manager_Fade = GetSafe(ContextObject))
			{
				Manager_Fade->SafeFade(Params);
				return true;
			}
			return false;
		#else
			UCsManager_Fade::Get()->SafeFade(Params);
			return true;
		#endif // #if WITH_EDITOR
		}

		void FLibrary::StopFadeChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->StopFade();
		}

		void FLibrary::ClearFadeChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->ClearFade();
		}

		bool FLibrary::SafeClearFade(const FString& Context, const UObject* ContextObject, LogWarning)
		{
			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject, Log))
			{
				Manager_Fade->ClearFade();
				return true;
			}
			return false;
		}

		void FLibrary::FadeBlackToBlackChecked(const FString& Context, const UObject* ContextObject, const float& Time)
		{
			ParamsType Params;
			Params.SetFrom(FLinearColor::Black); 
			Params.SetTo(FLinearColor::Black);
			Params.SetTime(Time);

			GetChecked(Context, ContextObject)->SafeFade(Params);
		}

		bool FLibrary::SafeFadeBlackToBlack(const FString& Context, const UObject* ContextObject, const float& Time, LogWarning)
		{
			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject))
			{
				ParamsType Params;
				Params.SetFrom(FLinearColor::Black); 
				Params.SetTo(FLinearColor::Black);
				Params.SetTime(Time);

				Manager_Fade->SafeFade(Params);
				return false;
			}
			return true;
		}
		
		void FLibrary::FadeClearToBlackChecked(const FString& Context, const UObject* ContextObject, const float& Time)
		{
			ParamsType Params;
			Params.SetFrom(FLinearColor::Transparent); 
			Params.SetTo(FLinearColor::Black);
			Params.SetTime(Time);

			GetChecked(Context, ContextObject)->SafeFade(Params);
		}

		bool FLibrary::SafeFadeClearToBlack(const FString& Context, const UObject* ContextObject, const float& Time, LogWarning)
		{
			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject, Log))
			{
				ParamsType Params;
				Params.SetFrom(FLinearColor::Transparent);
				Params.SetTo(FLinearColor::Black);
				Params.SetTime(Time);

				Manager_Fade->SafeFade(Params);
				return true;
			}
			return false;
		}

		void FLibrary::FadeBlackToClearChecked(const FString& Context, const UObject* ContextObject, const float& Time)
		{
			ParamsType Params;
			Params.SetFrom(FLinearColor::Black); 
			Params.SetTo(FLinearColor::Transparent);
			Params.SetTime(Time);
			Params.SetbCollapseOnEnd(true);

			GetChecked(Context, ContextObject)->SafeFade(Params);
		}

		bool FLibrary::SafeFadeBlackToClear(const FString& Context, const UObject* ContextObject, const float& Time, LogWarning)
		{
			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject, Log))
			{
				ParamsType Params;
				Params.SetFrom(FLinearColor::Black);
				Params.SetTo(FLinearColor::Transparent);
				Params.SetTime(Time);
				Params.SetbCollapseOnEnd(true);

				Manager_Fade->SafeFade(Params);
				return true;
			}
			return false;
		}

		#undef ParamsType

		#define OnCompleteEventType NCsFade::NManager::NFade::FOnComplete

		OnCompleteEventType& FLibrary::GetOnFadeComplete_EventChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->GetOnFadeComplete_Event();
		}

		bool FLibrary::IsFadeCompleteChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetChecked(Context, ContextObject)->IsFadeComplete();
		}

		bool FLibrary::IsFadeActiveChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetChecked(Context, WorldContext)->IsFadeActive();
		}

		bool FLibrary::SafeIsFadeActive(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogWarning)
		{
			OutSuccess = false;

			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, WorldContext, Log))
			{
				OutSuccess = true;

				return Manager_Fade->IsFadeActive();
			}
			return OutSuccess;
		}

		#undef OnCompleteEventType

		#undef LogWarning
	}
}