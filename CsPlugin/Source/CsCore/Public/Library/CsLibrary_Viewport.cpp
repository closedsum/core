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
			bool FLibrary::CanProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetFirstLocalChecked(Context, WorldContext);

				checkf(LocalPlayer->ViewportClient, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				return true;
			}

			bool FLibrary::CanDeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetFirstLocalChecked(Context, WorldContext);

				checkf(LocalPlayer->ViewportClient, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				return true;
			}

			bool FLibrary::DeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection)
			{
				check(CanDeprojectScreenToWorldChecked(Context, WorldContext));

				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetFirstLocalChecked(Context, WorldContext);

				UGameViewportClient* GVC = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				FViewport* Viewport = GVC->Viewport;

				checkf(Viewport, TEXT("%s: Failed to get Viewport from ViewportClient: %s for LocalPlayer: %s."), *Context, *(GVC->GetName()), *(LocalPlayer->GetName()));

				// Get the projection data
				FSceneViewProjectionData ProjectionData;
				if (LocalPlayer->GetProjectionData(Viewport, eSSP_FULL, /*out*/ ProjectionData))
				{
					FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
					FSceneView::DeprojectScreenToWorld(ScreenPosition, ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ WorldPosition, /*out*/ WorldDirection);
					return true;
				}

				// Something went wrong, zero things and return false
				WorldPosition  = FVector::ZeroVector;
				WorldDirection = FVector::ZeroVector;
				return false;
			}

			FSceneViewport* FLibrary::GetViewportChecked(const FString& Context, const UObject* WorldContext)
			{
				typedef NCsPlayer::FLibrary PlayerLibrary;

				ULocalPlayer* LocalPlayer = PlayerLibrary::GetFirstLocalChecked(Context, WorldContext);
				UGameViewportClient* GVC  = LocalPlayer->ViewportClient;

				checkf(GVC, TEXT("%s: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

				FSceneViewport* SV = GVC->GetGameViewport();

				checkf(SV, TEXT("%s: Failed get Viewport from LocalPlayer: %s with ViewportClient: %s."), *Context, *(LocalPlayer->GetName()), *(GVC->GetName()));
		
				return SV;
			}

			FIntPoint FLibrary::GetSizeChecked(const FString& Context, const UObject* WorldContext)
			{
				FSceneViewport* SV = GetViewportChecked(Context, WorldContext);

				return SV->GetSizeXY();
			}
		}
	}
}