// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Fade/CsLibrary_Manager_Fade.h"

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

		UCsManager_Fade* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsPlayback::FLog::Warning*/)
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

		UCsManager_Fade* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) /*= &NCsPlayback::FLog::Warning*/)
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

		#undef ParamsType

		void FLibrary::StopFadeChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->StopFade();
		}

		void FLibrary::ClearFadeChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->ClearFade();
		}

		bool FLibrary::SafeClearFade(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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
			typedef NCsFade::FParams FadeParamsType;

			FadeParamsType Params;
			Params.From = FLinearColor::Black; 
			Params.To	= FLinearColor::Black;
			Params.Time = Time;

			GetChecked(Context, ContextObject)->SafeFade(Params);
		}

		bool FLibrary::SafeFadeBlackToBlack(const FString& Context, const UObject* ContextObject, const float& Time, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject))
			{
				typedef NCsFade::FParams FadeParamsType;

				FadeParamsType Params;
				Params.From = FLinearColor::Black; 
				Params.To	= FLinearColor::Black;
				Params.Time = Time;

				Manager_Fade->SafeFade(Params);
				return false;
			}
			return true;
		}
		
		void FLibrary::FadeClearToBlackChecked(const FString& Context, const UObject* ContextObject, const float& Time)
		{
			typedef NCsFade::FParams FadeParamsType;

			FadeParamsType Params;
			Params.From = FLinearColor::Transparent; 
			Params.To	= FLinearColor::Black;
			Params.Time = Time;

			GetChecked(Context, ContextObject)->SafeFade(Params);
		}

		bool FLibrary::SafeFadeClearToBlack(const FString& Context, const UObject* ContextObject, const float& Time, void(*Log)(const FString&)/*=&FCsLog::Warning*/)
		{
			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject, Log))
			{
				typedef NCsFade::FParams ParamsType;

				ParamsType Params;
				Params.From = FLinearColor::Transparent;
				Params.To   = FLinearColor::Black;
				Params.Time = Time;

				Manager_Fade->SafeFade(Params);
				return true;
			}
			return false;
		}

		void FLibrary::FadeBlackToClearChecked(const FString& Context, const UObject* ContextObject, const float& Time)
		{
			typedef NCsFade::FParams FadeParamsType;

			FadeParamsType Params;
			Params.From = FLinearColor::Black; 
			Params.To	= FLinearColor::Transparent;
			Params.Time = Time;
			Params.bCollapseOnEnd = true;

			GetChecked(Context, ContextObject)->SafeFade(Params);
		}

		bool FLibrary::SafeFadeBlackToClear(const FString& Context, const UObject* ContextObject, const float& Time, void(*Log)(const FString&)/*=&FCsLog::Warning*/)
		{
			typedef NCsFade::FParams ParamsType;

			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject, Log))
			{
				ParamsType Params;
				Params.From = FLinearColor::Black;
				Params.To	= FLinearColor::Transparent;
				Params.Time = Time;
				Params.bCollapseOnEnd = true;

				Manager_Fade->SafeFade(Params);
				return true;
			}
			return false;
		}
	}
}