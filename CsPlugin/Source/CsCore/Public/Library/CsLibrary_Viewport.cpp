// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Viewport.h"
#include "CsCore.h"

// Player
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
// World
#include "Engine/World.h"

namespace NCsViewport
{
	bool FLibrary::CanProjectWorldToScreenChecked(const FString& Context, UObject* WorldContext)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		APlayerController* PlayerController = World->GetFirstPlayerController();

		checkf(PlayerController, TEXT("%s: PlayerController is NULL."));

		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

		checkf(LocalPlayer, TEXT("%s: LocalPlayer is NULL for PlayerController: %s."), *(PlayerController->GetName()));

		checkf(LocalPlayer->ViewportClient, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

		return true;
	}
}