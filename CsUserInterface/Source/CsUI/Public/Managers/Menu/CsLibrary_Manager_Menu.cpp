// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "Managers/Menu/CsLibrary_Manager_Menu.h"
#include "CsUI.h"

// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsMenu
{
	namespace NManager
	{
		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, GameInstance);

			return GameInstance;
		}
	}
}