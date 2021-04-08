// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsLibrary_Manager_Javascript.h"

// World
#include "Engine/World.h"

#if WITH_EDITOR
// Game
#include "Engine/GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsJs
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

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, GameInstance);

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

		UObject* FLibrary::GetEngineContextRoot()
		{
			return GEngine;
		}
	}
}