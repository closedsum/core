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
	namespace NMouse
	{
		bool FLibrary::IsShowingCursorChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			return PC->bShowMouseCursor;
		}

		void FLibrary::ShowCursorChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			PC->bShowMouseCursor = true;
		}

		void FLibrary::HideCursorChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			PC->bShowMouseCursor = false;
		}

		void FLibrary::GetPositionChecked(const FString& Context, UObject* WorldContext, FIntPoint& Position)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			SV->GetMousePos(Position);
		}


		void FLibrary::SetPositionChecked(const FString& Context, UObject* WorldContext, const int32& X, const int32& Y)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			SV->SetMouse(X, Y);
		}

		void FLibrary::SetCenterOfViewportChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			const FIntPoint Size = SV->GetSizeXY();

			SV->SetMouse(Size.X / 2, Size.Y / 2);
		}

		void FLibrary::RefreshPositionChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			FIntPoint Position;

			SV->GetMousePos(Position);

			const FIntPoint Size = SV->GetSizeXY();

			SV->SetMouse(Size.X / 2, Size.Y / 2);
			SV->SetMouse(Position.X, Position.Y);
		}
	}

	namespace NTouch
	{
		bool FLibrary::GetPositionChecked(const FString& Context, UObject* WorldContext, const ETouchIndex::Type& FingerIndex, FIntPoint& Position)
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
}