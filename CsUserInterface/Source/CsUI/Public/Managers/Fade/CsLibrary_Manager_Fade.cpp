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
		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

			return GameInstance;
		}

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