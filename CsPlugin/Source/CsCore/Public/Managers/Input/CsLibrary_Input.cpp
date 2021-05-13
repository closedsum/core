// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsLibrary_Input.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
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
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeIsShowingCursor);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeShowCursor);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeHideCursor);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, GetSafePosition);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SetSafePosition);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, GetSafeWorldIntersection);
				}
			}
		}

		// Show / Hide
		#pragma region

		bool FLibrary::IsShowingCursorChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			return PC->bShowMouseCursor;
		}

		bool FLibrary::SafeIsShowingCursor(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

			return PC ? PC->bShowMouseCursor : false;
		}

		bool FLibrary::SafeIsShowingCursor(const UObject* WorldContext)
		{
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::SafeIsShowingCursor;

			return SafeIsShowingCursor(Context, WorldContext, nullptr);
		}

		void FLibrary::ShowCursorChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			PC->bShowMouseCursor = true;
		}

		void FLibrary::SafeShowCursor(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

			if (PC)
				PC->bShowMouseCursor = true;
		}

		void FLibrary::SafeShowCursor(const UObject* WorldContext)
		{
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::SafeShowCursor;

			return SafeShowCursor(Context, WorldContext, nullptr);
		}

		void FLibrary::HideCursorChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			PC->bShowMouseCursor = false;
		}

		void FLibrary::SafeHideCursor(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetSafeFirstLocal(Context, WorldContext, Log);

			if (PC)
				PC->bShowMouseCursor = false;
		}

		void FLibrary::SafeHideCursor(const UObject* WorldContext)
		{
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::SafeHideCursor;

			return SafeHideCursor(Context, WorldContext, nullptr);
		}

		#pragma endregion Show / Hide

		// Get / Set
		#pragma region

		void FLibrary::GetPositionChecked(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			SV->GetMousePos(OutPosition);
		}

		void FLibrary::GetSafePosition(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			OutPosition = FIntPoint::NoneValue;

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetSafeViewport(Context, WorldContext, Log);

			if (SV)
				SV->GetMousePos(OutPosition);
		}

		void FLibrary::GetSafePosition(const UObject* WorldContext, FIntPoint& OutPosition)
		{
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::GetSafePosition;

			GetSafePosition(Context, WorldContext, OutPosition, nullptr);
		}

		void FLibrary::SetPositionChecked(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			SV->SetMouse(X, Y);
		}

		void FLibrary::SetSafePosition(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetSafeViewport(Context, WorldContext);

			if (SV)
				SV->SetMouse(X, Y);
		}

		void FLibrary::SetSafePosition(const UObject* WorldContext, const int32& X, const int32& Y)
		{
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::SetSafePosition;

			SetSafePosition(Context, WorldContext, X, Y, nullptr);
		}

		void FLibrary::SetCenterOfViewportChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			const FIntPoint Size = SV->GetSizeXY();

			SV->SetMouse(Size.X / 2, Size.Y / 2);
		}

		#pragma endregion Get / Set

		void FLibrary::RefreshPositionChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			FIntPoint Position;

			SV->GetMousePos(Position);

			const FIntPoint Size = SV->GetSizeXY();

			SV->SetMouse(Size.X / 2, Size.Y / 2);
			SV->SetMouse(Position.X, Position.Y);
		}

		bool FLibrary::GetWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FPlane& Plane, FVector& OutIntersection)
		{
			FIntPoint Position;
			GetPositionChecked(Context, WorldContext, Position);

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			return ViewportLibrary::GetScreenWorldIntersectionChecked(Context, WorldContext, Position, Plane, OutIntersection);
		}

		bool FLibrary::GetSafeWorldIntersection(const FString& Context, const UObject* WorldContext, const FPlane& Plane, FVector& OutIntersection, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			FIntPoint Position;
			GetSafePosition(Context, WorldContext, Position, Log);

			if (Position == FIntPoint::NoneValue)
				return false;

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			return ViewportLibrary::GetSafeScreenWorldIntersection(Context, WorldContext, Position, Plane, OutIntersection, Log);
		}

		bool FLibrary::GetSafeWorldIntersection(const UObject* WorldContext, const FPlane& Plane, FVector& OutIntersection)
		{
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::GetSafeWorldIntersection;

			return GetSafeWorldIntersection(Context, WorldContext, Plane, OutIntersection, nullptr);
		}
	}

	namespace NTouch
	{
		bool FLibrary::GetPositionChecked(const FString& Context, const UObject* WorldContext, const ETouchIndex::Type& FingerIndex, FIntPoint& OutPosition)
		{
			checkf((int32)FingerIndex < EKeys::NUM_TOUCH_KEYS, TEXT("%s: FingerIndex is NOT Valid."), *Context);

			typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

			APlayerController* PC = PlayerControllerLibrary::GetFirstLocalChecked(Context, WorldContext);

			UPlayerInput* PlayerInput = PC->PlayerInput;

			checkf(PlayerInput, TEXT("%s: PlayerInput is NULL for PlayerController: %s."), *Context, *(PC->GetName()));

			OutPosition = FIntPoint::NoneValue;

			if (PlayerInput->Touches[(uint8)FingerIndex].Z != 0.0f)
			{
				const float& X = PlayerInput->Touches[FingerIndex].X;
				const float& Y = PlayerInput->Touches[FingerIndex].Y;

				typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

				const FIntPoint Size = ViewportLibrary::GetSizeChecked(Context, WorldContext);

				OutPosition.X = FMath::FloorToInt(X * Size.X);
				OutPosition.Y = FMath::FloorToInt(Y * Size.Y);
				return true;
			}
			return false;
		}
	}
}