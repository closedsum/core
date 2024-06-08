// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Input/CsLibrary_Input_Mouse.h"

// Library
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
// UI
#include "Slate/SceneViewport.h"

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
					// Show / Hide
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeIsShowingCursor);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeShowCursor);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeHideCursor);
					// Get / Set
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, GetSafePosition);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SetSafePosition);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, GetSafeWorldIntersection);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeTrace);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsInput::NMouse::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsInput::NMouse::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/
		#define PCFirstLocalLibrary NCsPlayer::NController::NLocal::NFirst::FLibrary
		#define ViewportLibrary NCsViewport::NLocal::NPlayer::FLibrary 

		// Show / Hide
		#pragma region

		bool FLibrary::IsShowingCursorChecked(const FString& Context, const UObject* WorldContext)
		{
			return PCFirstLocalLibrary::GetChecked(Context, WorldContext)->bShowMouseCursor;
		}

		bool FLibrary::SafeIsShowingCursor(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			APlayerController* PC = PCFirstLocalLibrary::GetSafe(Context, WorldContext, Log);

			return PC ? PC->bShowMouseCursor : false;
		}

		bool FLibrary::SafeIsShowingCursor(const UObject* WorldContext)
		{
			SET_CONTEXT(SafeIsShowingCursor);

			return SafeIsShowingCursor(Context, WorldContext, nullptr);
		}

		void FLibrary::ShowCursorChecked(const FString& Context, const UObject* WorldContext)
		{
			PCFirstLocalLibrary::GetChecked(Context, WorldContext)->bShowMouseCursor = true;
		}

		bool FLibrary::SafeShowCursor(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (APlayerController* PC = PCFirstLocalLibrary::GetSafe(Context, WorldContext, Log))
			{
				PC->bShowMouseCursor = true;
				return true;
			}
			return false;
		}

		bool FLibrary::SafeShowCursor(const UObject* WorldContext)
		{
			SET_CONTEXT(SafeShowCursor);

			return SafeShowCursor(Context, WorldContext, nullptr);
		}

		void FLibrary::HideCursorChecked(const FString& Context, const UObject* WorldContext)
		{
			PCFirstLocalLibrary::GetChecked(Context, WorldContext)->bShowMouseCursor  = false;
		}

		bool FLibrary::SafeHideCursor(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (APlayerController* PC = PCFirstLocalLibrary::GetSafe(Context, WorldContext, Log))
			{
				PC->bShowMouseCursor = false;
				return true;
			}
			return false;
		}

		bool FLibrary::SafeHideCursor(const UObject* WorldContext)
		{
			SET_CONTEXT(SafeHideCursor);

			return SafeHideCursor(Context, WorldContext, nullptr);
		}

		#pragma endregion Show / Hide

		// Get / Set
		#pragma region

		void FLibrary::GetPositionChecked(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition)
		{
			ViewportLibrary::GetViewportChecked(Context, WorldContext)->GetMousePos(OutPosition);
		}

		bool FLibrary::GetSafePosition(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition, LogLevel)
		{
			OutPosition = FIntPoint::NoneValue;

			if (FSceneViewport* SV = ViewportLibrary::GetSafeViewport(Context, WorldContext, Log))
			{
				SV->GetMousePos(OutPosition);

				if (OutPosition == FIntPoint::NoneValue)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get a valid mouse position from Viewport."), *Context));
				}
				return OutPosition != FIntPoint::NoneValue;
			}
			return false;
		}

		bool FLibrary::GetSafePosition(const UObject* WorldContext, FIntPoint& OutPosition)
		{
			SET_CONTEXT(GetSafePosition);

			return GetSafePosition(Context, WorldContext, OutPosition, nullptr);
		}

		void FLibrary::SetPositionChecked(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y)
		{
			ViewportLibrary::GetViewportChecked(Context, WorldContext)->SetMouse(X, Y);
		}

		bool FLibrary::SetSafePosition(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y, LogLevel)
		{
			if (FSceneViewport* SV = ViewportLibrary::GetSafeViewport(Context, WorldContext))
			{
				SV->SetMouse(X, Y);
				return true;
			}
			return false;
		}

		bool FLibrary::SetSafePosition(const UObject* WorldContext, const int32& X, const int32& Y)
		{
			SET_CONTEXT(SetSafePosition);

			return SetSafePosition(Context, WorldContext, X, Y, nullptr);
		}

		void FLibrary::SetCenterOfViewportChecked(const FString& Context, const UObject* WorldContext)
		{
			FSceneViewport* SV   = ViewportLibrary::GetViewportChecked(Context, WorldContext);
			const FIntPoint Size = SV->GetSizeXY();

			SV->SetMouse(Size.X / 2, Size.Y / 2);
		}

		bool FLibrary::SetSafeCenterOfViewport(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (FSceneViewport* SV = ViewportLibrary::GetSafeViewport(Context, WorldContext, Log))
			{
				const FIntPoint Size = SV->GetSizeXY();

				SV->SetMouse(Size.X / 2, Size.Y / 2);
				return true;
			}
			return false;
		}

		bool FLibrary::GetSafeDeprojectToWorld(const FString& Context, const UObject* WorldContext, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection, LogLevel)
		{
			FIntPoint Position;
			GetSafePosition(Context, WorldContext, Position, Log);

			if (Position == FIntPoint::NoneValue)
				return false;
			return ViewportLibrary::SafeDeprojectScreenToWorld(Context, WorldContext, FVector2f(Position.X, Position.Y), OutWorldPosition, OutWorldDirection, Log);
		}

		#pragma endregion Get / Set

		void FLibrary::RefreshPositionChecked(const FString& Context, const UObject* WorldContext)
		{
			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			FIntPoint Position;

			SV->GetMousePos(Position);

			const FIntPoint Size = SV->GetSizeXY();

			SV->SetMouse(Size.X / 2, Size.Y / 2);
			SV->SetMouse(Position.X, Position.Y);
		}

		bool FLibrary::SafeRefreshPosition(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (FSceneViewport* SV = ViewportLibrary::GetSafeViewport(Context, WorldContext, Log))
			{
				FIntPoint Position;

				SV->GetMousePos(Position);

				const FIntPoint Size = SV->GetSizeXY();

				SV->SetMouse(Size.X / 2, Size.Y / 2);
				SV->SetMouse(Position.X, Position.Y);
				return true;
			}
			return false;
		}

		bool FLibrary::GetWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FPlane4f& Plane, FVector3f& OutIntersection)
		{
			FIntPoint Position;
			GetPositionChecked(Context, WorldContext, Position);
			return ViewportLibrary::GetScreenWorldIntersectionChecked(Context, WorldContext, Position, Plane, OutIntersection);
		}

		bool FLibrary::GetSafeWorldIntersection(const FString& Context, const UObject* WorldContext, const FPlane4f& Plane, FVector3f& OutIntersection, LogLevel)
		{
			FIntPoint Position;
			GetSafePosition(Context, WorldContext, Position, Log);

			if (Position == FIntPoint::NoneValue)
				return false;
			return ViewportLibrary::GetSafeScreenWorldIntersection(Context, WorldContext, Position, Plane, OutIntersection, Log);
		}

		bool FLibrary::GetSafeWorldIntersection(const UObject* WorldContext, const FPlane4f& Plane, FVector3f& OutIntersection)
		{
			SET_CONTEXT(GetSafeWorldIntersection);

			return GetSafeWorldIntersection(Context, WorldContext, Plane, OutIntersection, nullptr);
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
		#undef PCFirstLocalLibrary
		#undef ViewportLibrary
	}
}