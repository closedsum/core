// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Fade/CsLibrary_Manager_Fade.h"

// Managers
#include "Managers/Fade/CsManager_Fade.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsFade
{
	namespace NManager
	{
	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

			return GameInstance;
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* WorldContext)
		{
			if (!WorldContext)
				return nullptr;

			UWorld* World = WorldContext->GetWorld();

			if (!World)
				return nullptr;

			return World->GetGameInstance();
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