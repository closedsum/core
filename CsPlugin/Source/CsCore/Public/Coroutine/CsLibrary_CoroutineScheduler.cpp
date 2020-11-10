// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coroutine/CsLibrary_CoroutineScheduler.h"

// Actor
#include "GameFramework/Actor.h"
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
		UObject* FLibrary::GetContextRoot(AActor* Actor)
		{
			checkf(Actor, TEXT("FLibrary::GetContextRoot: Actor is NULL."));

#if WITH_EDITOR
			if (FCsLibrary_World::IsPlayInEditor(Actor->GetWorld()) ||
				FCsLibrary_World::IsPlayInEditorPreview(Actor->GetWorld()))
			{
				return GEngine;
			}
			else
#endif // #if WITH_EDITOR
			{
				return Actor->GetWorld()->GetGameInstance();
			}
		}
	}
}