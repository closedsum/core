// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Input/CsLibrary_Input_Touch.h"

// Library
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"

namespace NCsInput
{
	namespace NTouch
	{
		#define PCFirstLocalLibrary NCsPlayer::NController::NLocal::NFirst::FLibrary
		#define ViewportLibrary NCsViewport::NLocal::NPlayer::FLibrary 

		bool FLibrary::GetPositionChecked(const FString& Context, const UObject* WorldContext, const ETouchIndex::Type& FingerIndex, FIntPoint& OutPosition)
		{
			checkf((int32)FingerIndex < EKeys::NUM_TOUCH_KEYS, TEXT("%s: FingerIndex is NOT Valid."), *Context);

			APlayerController* PC	  = PCFirstLocalLibrary::GetChecked(Context, WorldContext);
			UPlayerInput* PlayerInput = PC->PlayerInput;

			checkf(PlayerInput, TEXT("%s: PlayerInput is NULL for PlayerController: %s."), *Context, *(PC->GetName()));

			OutPosition = FIntPoint::NoneValue;

			if (PlayerInput->Touches[(uint8)FingerIndex].Z != 0.0f)
			{
				const float& X = PlayerInput->Touches[FingerIndex].X;
				const float& Y = PlayerInput->Touches[FingerIndex].Y;

				const FIntPoint Size = ViewportLibrary::GetSizeChecked(Context, WorldContext);

				OutPosition.X = FMath::FloorToInt(X * Size.X);
				OutPosition.Y = FMath::FloorToInt(Y * Size.Y);
				return true;
			}
			return false;
		}

		#undef PCFirstLocalLibrary
		#undef ViewportLibrary
	}
}