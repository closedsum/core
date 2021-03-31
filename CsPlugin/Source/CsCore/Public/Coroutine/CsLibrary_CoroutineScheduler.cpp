// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
// Engine
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

namespace NCsCoroutine
{
	namespace NScheduler
	{
	#if WITH_EDITOR

		UObject* FLibrary::GetContextRoot(UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("FLibrary::GetContextRoot: WorldContext is NULL."));

			if (FCsLibrary_World::IsPlayInEditor(WorldContext->GetWorld()) ||
				FCsLibrary_World::IsPlayInEditorPreview(WorldContext->GetWorld()))
			{
				return GEngine;
			}
			else
			{
				return WorldContext->GetWorld()->GetGameInstance();
			}
		}

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			if (FCsLibrary_World::IsPlayInEditor(World) ||
				FCsLibrary_World::IsPlayInEditorPreview(World))
			{
				return GEngine;
			}

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

			if (FCsLibrary_World::IsPlayInEditor(WorldContext->GetWorld()) ||
				FCsLibrary_World::IsPlayInEditorPreview(WorldContext->GetWorld()))
			{
				return GEngine;
			}
			else

			{
				return World->GetGameInstance();
			}
		}

	#endif // #if WITH_EDITOR
	}
}