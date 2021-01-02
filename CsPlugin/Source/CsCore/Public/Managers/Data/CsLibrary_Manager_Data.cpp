// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/CsLibrary_Manager_Data.h"
#include "CsCore.h"

// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsData
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

			return World->GetGameInstance();
		}

		UObject* FLibrary::GetContextRoot(const FString& Context, UObject* WorldContext)
		{
			if (!WorldContext)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: WorldContext is NULL."), *Context);
				return nullptr;
			}

			UWorld* World = WorldContext->GetWorld();

			if (!World)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));
				return nullptr;
			}

			UGameInstance* GameInstance = World->GetGameInstance();

			if (!GameInstance)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));
			}
			return GameInstance;
		}

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

			return GameInstance;
		}
	}
}