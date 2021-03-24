// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/ConsoleCommand/CsLibrary_Coordinator_ConsoleCommand.h"
#include "CsCore.h"

// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsConsoleCommand
{
	namespace NCoordinator
	{
	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			UGameInstance* GameInstance = World->GetGameInstance();

			checkf(GameInstance, TEXT("%s: Failed to get GameInstance from World: %s."), *Context, *(World->GetName()));

			return GameInstance;
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* WorldContext)
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

		#endif // #if WITH_EDITOR
	}
}