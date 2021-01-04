// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Viewport.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Player.h"
// Player
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
// World
#include "Engine/World.h"
// View
#include "Engine/GameViewportClient.h"
#include "Slate/SceneViewport.h"

namespace NCsViewport
{
	namespace NLocal
	{
		namespace NPlayer
		{
			bool FLibrary::CanProjectWorldToScreenChecked(const FString& Context, UObject* WorldContext)
			{
				ULocalPlayer* LocalPlayer = FCsLibrary_Player::GetFirstLocalPlayerChecked(Context, WorldContext);

				checkf(LocalPlayer->ViewportClient, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				return true;
			}

			FSceneViewport* FLibrary::GetViewportChecked(const FString& Context, UObject* WorldContext)
			{
				ULocalPlayer* LocalPlayer = FCsLibrary_Player::GetFirstLocalPlayerChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				FSceneViewport* SV = GVC->GetGameViewport();

				checkf(SV, TEXT("%s: Failed get Viewport from LocalPlayer: %s with ViewportClient: %s."), *Context, *(LocalPlayer->GetName()), *(GVC->GetName()));
		
				return SV;
			}

			FIntPoint FLibrary::GetSizeChecked(const FString& Context, UObject* WorldContext)
			{
				FSceneViewport* SV = GetViewportChecked(Context, WorldContext);

				return SV->GetSizeXY();
			}
		}
	}
}