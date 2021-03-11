// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsLibrary_Manager_Time.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
#endif // #if WITH_EDITOR

namespace NCsTime
{
	namespace NManager
	{
		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

#if WITH_EDITOR
			if (FCsLibrary_World::IsPlayInEditor(World) ||
				FCsLibrary_World::IsPlayInEditorPreview(World))
			{
				return GEngine;
			}
#endif // #if WITH_EDITOR

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

#if WITH_EDITOR
			if (FCsLibrary_World::IsPlayInEditor(WorldContext->GetWorld()) ||
				FCsLibrary_World::IsPlayInEditorPreview(WorldContext->GetWorld()))
			{
				return GEngine;
			}
			else
#endif // #if WITH_EDITOR
			{
				return World->GetGameInstance();
			}
		}

		void FLibrary::UpdateTimeAndCoroutineScheduler(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group, const float& DeltaTime)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_Time* Manager_Time = UCsManager_Time::Get(ContextRoot);

			Manager_Time->Update(Group, DeltaTime);

			const FCsDeltaTime& ScaledDeltaTime = Manager_Time->GetScaledDeltaTime(Group);

			// Update CoroutineScheduler
			UCsCoroutineScheduler::Get(ContextRoot)->Update(Group, ScaledDeltaTime);
		}

		void FLibrary::SetScaledDeltaTime(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group, const float& Scale)
		{
			UCsManager_Time::Get(GetContextRootChecked(Context, WorldContext))->SetScaledDeltaTime(Group, Scale);
		}

		void FLibrary::ResetScaledDeltaTime(const FString& Context, UObject* WorldContext, const FECsUpdateGroup& Group)
		{
			UCsManager_Time::Get(GetContextRootChecked(Context, WorldContext))->ResetScaledDeltaTime(Group);
		}
	}
}