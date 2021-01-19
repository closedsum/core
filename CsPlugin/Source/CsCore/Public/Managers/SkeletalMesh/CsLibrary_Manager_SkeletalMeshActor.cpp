// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/CsLibrary_Manager_SkeletalMeshActor.h"

// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

namespace NCsSkeletalMeshActor
{
	namespace NManager
	{
		UObject* FLibrary::GetContextRoot(UObject* WorldContext)
		{
			if (!WorldContext)
				return nullptr;

			UWorld* World = WorldContext->GetWorld();

			if (!World)
				return nullptr;

			AGameStateBase* GameState = World->GetGameState();

			if (!GameState)
				return nullptr;
			return GameState;
		}

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			AGameStateBase* GameState = World->GetGameState();

			checkf(GameState, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));

			return GameState;
		}
	}
}