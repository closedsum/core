// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

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
		UObject* FLibrary::GetContextRoot(UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("FLibrary::GetContextRoot: WorldContext is NULL."));

#if WITH_EDITOR
			if (FCsLibrary_World::IsPlayInEditor(WorldContext->GetWorld()) ||
				FCsLibrary_World::IsPlayInEditorPreview(WorldContext->GetWorld()))
			{
				return GEngine;
			}
			else
#endif // #if WITH_EDITOR
			{
				return WorldContext->GetWorld()->GetGameInstance();
			}
		}
	}
}