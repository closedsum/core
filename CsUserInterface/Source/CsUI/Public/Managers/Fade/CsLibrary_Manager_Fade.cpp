// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Fade/CsLibrary_Manager_Fade.h"

// Managers
#include "Managers/Fade/CsManager_Fade.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
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

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

			return GameInstance;
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* WorldContext, void (*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;

			return World->GetGameInstance();
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* WorldContext)
		{
			using namespace NCsFade::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

	#endif // #if WITH_EDITOR

		void FLibrary::CreateFadeWidget(const FString& Context, UObject* WorldContext)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_Fade::Get(ContextRoot)->CreateFadeWidget();
		}

		#define ParamsType NCsFade::FParams
		void FLibrary::FadeChecked(const FString& Context, UObject* WorldContext, const ParamsType& Params)
		{
		#undef ParamsType

			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_Fade::Get(ContextRoot)->Fade(Params);
		}

		#define ParamsType NCsFade::FParams
		void FLibrary::SafeFade(UObject* WorldContext, const ParamsType& Params)
		{
		#undef ParamsType

		#if WITH_EDITOR
			if (UObject* ContextRoot = GetSafeContextRoot(WorldContext))
			{
				UCsManager_Fade::Get(ContextRoot)->SafeFade(Params);
			}
		#else
			UCsManager_Fade::Get()->SafeFade(Params);
		#endif // #if WITH_EDITOR
		}

		void FLibrary::StopFadeChecked(const FString& Context, UObject* WorldContext)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_Fade::Get(ContextRoot)->StopFade();
		}

		void FLibrary::ClearFadeChecked(const FString& Context, UObject* WorldContext)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_Fade::Get(ContextRoot)->ClearFade();
		}
	}
}