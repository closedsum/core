// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Actor.h"

// World
#include "Engine/World.h"

namespace NCsActor
{
	AActor* FLibrary::GetActorWithTagChecked(const FString& Context, UObject* WorldContext, const FName& Tag)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		checkf(Tag != NAME_None, TEXT("%s: Tag: None is NOT Valid."), *Context);

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

#if UE_BUILD_SHIPPING
		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
#else
		AActor* Actor = nullptr;

		for (TActorIterator<AActor> Itr(World); Itr; ++Itr)
		{
			AActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!A || A->IsPendingKill())
				continue;
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Actors with the Tag: %s."), *Context, *(Tag.ToString()));
				}
			}
		}

		if (Actor)
			return Actor;
#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Actor with Tag: %s."), *Context, *(Tag.ToString()));
		return nullptr;
	}
}