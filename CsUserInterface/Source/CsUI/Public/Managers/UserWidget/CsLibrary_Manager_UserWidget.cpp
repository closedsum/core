// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsLibrary_Manager_UserWidget.h"

// Managers
#include "Managers/UserWidget/CsManager_UserWidget.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

namespace NCsUserWidget
{
	namespace NManager
	{
	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			AGameStateBase* GameState = World->GetGameState();

			checkf(GameState, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));

			return GameState;
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* WorldContext)
		{
			if (!WorldContext)
				return nullptr;

			UWorld* World = WorldContext->GetWorld();

			if (!World)
				return nullptr;

			return World->GetGameState();
		}

	#endif // #if WITH_EDITOR
	}
}