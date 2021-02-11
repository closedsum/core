// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsLibrary_Manager_UserWidget.h"

// Managers
#include "Managers/UserWidget/CsManager_UserWidget.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

namespace NCsUserWidget
{
	namespace NManager
	{
		UObject* FLibrary::GetSafeContextRoot(UObject* WorldContext)
		{
			if (!WorldContext)
				return nullptr;

			UWorld* World = WorldContext->GetWorld();

			if (!World)
				return nullptr;

			return World->GetGameState();
		}
	}
}