// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Fade/CsLibrary_Manager_Fade.h"

// Managers
#include "Managers/Fade/CsManager_Fade.h"
// Library
#include "Library/CsLibrary_Valid.h"

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

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void (*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsFade::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

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
			}
			return Manager_Fade;
		}

		UCsManager_Fade* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsFade::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

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

		bool FLibrary::SafeFadeClearToBlack(const FString& Context, const UObject* ContextObject, const float& Time, void(*Log)(const FString&)/*=&FCsLog::Warning*/)
		{
			typedef NCsFade::FParams ParamsType;

			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)

				ParamsType Params;
				Params.From = FLinearColor::Transparent;
				Params.To   = FLinearColor::Black;
				Params.Time = Time;

				Manager_Fade->SafeFade(Params);
			}
			return false;
		}

		bool FLibrary::SafeFadeBlackToClear(const FString& Context, const UObject* ContextObject, const float& Time, void(*Log)(const FString&)/*=&FCsLog::Warning*/)
		{
			typedef NCsFade::FParams ParamsType;

			if (UCsManager_Fade* Manager_Fade = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Time, 0.0f)

				ParamsType Params;
				Params.From = FLinearColor::Black;
				Params.To	= FLinearColor::Transparent;
				Params.Time = Time;

				Manager_Fade->SafeFade(Params);
			}
			return false;
		}
	}
}