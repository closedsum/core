// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsLibrary_Input.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Viewport.h"
// Player
#include "GameFramework/PlayerController.h"
// UI
#include "Slate/SceneViewport.h"

namespace NCsInput
{
	void FLibrary::ShowMouseCursorChecked(const FString& Context, UObject* WorldContext)
	{
		typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

		APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

		PC->bShowMouseCursor = true;
	}

	void FLibrary::HideMouseCursorChecked(const FString& Context, UObject* WorldContext)
	{
		typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

		APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

		PC->bShowMouseCursor = false;
	}

	void FLibrary::GetMousePositionChecked(const FString& Context, UObject* WorldContext, FIntPoint& Position)
	{
		typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

		FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

		SV->GetMousePos(Position);
	}


	void FLibrary::SetMousePositionChecked(const FString& Context, UObject* WorldContext, const int32& X, const int32& Y)
	{
		typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

		FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

		SV->SetMouse(X, Y);
	}

	void FLibrary::SetMouseCenterOfViewportChecked(const FString& Context, UObject* WorldContext)
	{
		typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

		FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

		const FIntPoint Size = SV->GetSizeXY();

		SV->SetMouse(Size.X / 2, Size.Y / 2);
	}
}