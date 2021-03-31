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
	#if WITH_EDITOR

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