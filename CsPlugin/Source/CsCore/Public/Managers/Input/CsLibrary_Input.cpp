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
// Input
#include "GameFramework/PlayerInput.h"

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

	bool FLibrary::GetTouchPositionChecked(const FString& Context, UObject* WorldContext, const ETouchIndex::Type& FingerIndex, FIntPoint& Position)
	{
		checkf((int32)FingerIndex < EKeys::NUM_TOUCH_KEYS, TEXT("%s: FingerIndex is NOT Valid."), *Context);

		typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

		APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

		UPlayerInput* PlayerInput = PC->PlayerInput;

		checkf(PlayerInput, TEXT("%s: PlayerInput is NULL for PlayerController: %s."), *Context, *(PC->GetName()));

		Position = FIntPoint::NoneValue;

		if (PlayerInput->Touches[(uint8)FingerIndex].Z != 0.0f)
		{
			const float& X = PlayerInput->Touches[FingerIndex].X;
			const float& Y = PlayerInput->Touches[FingerIndex].Y;

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			const FIntPoint Size = ViewportLibrary::GetSizeChecked(Context, WorldContext);

			Position.X = FMath::FloorToInt(X * Size.X);
			Position.Y = FMath::FloorToInt(Y * Size.Y);
			return true;
		}
		return false;
	}
}