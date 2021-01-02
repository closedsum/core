// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsLibrary_Manager_Sound.h"

// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
// Engine
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

namespace NCsSound
{
	namespace NManager
	{
		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			/*
#if WITH_EDITOR
			if (FCsLibrary_World::IsPlayInEditor(WorldContext->GetWorld()) ||
				FCsLibrary_World::IsPlayInEditorPreview(WorldContext->GetWorld()))
			{
				return WorldContext;
			}
			else
#endif // #if WITH_EDITOR
			{	
				return World->GetGameInstance();
			}
			*/
			AGameStateBase* GameState = World->GetGameState();

			checkf(GameState, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));

			return GameState;
		}
	}
}