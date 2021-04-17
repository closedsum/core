// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Fade/CsLibrary_Manager_Fade.h"

// Managers
#include "Managers/Fade/CsManager_Fade.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"
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
				}
			}
		}

	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* ContextObject, void (*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* ContextObject)
		{
			using namespace NCsFade::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

	#endif // #if WITH_EDITOR

		void FLibrary::CreateFadeWidget(const FString& Context, UObject* ContextObject)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, ContextObject);

			UCsManager_Fade::Get(ContextRoot)->CreateFadeWidget();
		}

		#define ParamsType NCsFade::FParams
		void FLibrary::FadeChecked(const FString& Context, UObject* ContextObject, const ParamsType& Params)
		{
		#undef ParamsType

			UObject* ContextRoot = GetContextRootChecked(Context, ContextObject);

			UCsManager_Fade::Get(ContextRoot)->Fade(Params);
		}

		#define ParamsType NCsFade::FParams
		void FLibrary::SafeFade(UObject* ContextObject, const ParamsType& Params)
		{
		#undef ParamsType

		#if WITH_EDITOR
			if (UObject* ContextRoot = GetSafeContextRoot(ContextObject))
			{
				UCsManager_Fade::Get(ContextRoot)->SafeFade(Params);
			}
		#else
			UCsManager_Fade::Get()->SafeFade(Params);
		#endif // #if WITH_EDITOR
		}

		void FLibrary::StopFadeChecked(const FString& Context, UObject* ContextObject)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, ContextObject);

			UCsManager_Fade::Get(ContextRoot)->StopFade();
		}

		void FLibrary::ClearFadeChecked(const FString& Context, UObject* ContextObject)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, ContextObject);

			UCsManager_Fade::Get(ContextRoot)->ClearFade();
		}
	}
}