// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsLibrary_Input.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "GameFramework/InputSettings.h"
// Player
#include "GameFramework/PlayerController.h"
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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeIsShowingCursor);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeShowCursor);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeHideCursor);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, GetSafePosition);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SetSafePosition);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, GetSafeWorldIntersection);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsInput::NMouse::FLibrary, SafeTrace);
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

		bool FLibrary::GetSafePosition(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			OutPosition = FIntPoint::NoneValue;

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetSafeViewport(Context, WorldContext, Log);

			if (SV)
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
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::GetSafePosition;

			return GetSafePosition(Context, WorldContext, OutPosition, nullptr);
		}

		void FLibrary::SetPositionChecked(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			SV->SetMouse(X, Y);
		}

		bool FLibrary::SetSafePosition(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetSafeViewport(Context, WorldContext);

			if (SV)
			{
				SV->SetMouse(X, Y);
				return true;
			}
			return false;
		}

		bool FLibrary::SetSafePosition(const UObject* WorldContext, const int32& X, const int32& Y)
		{
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::SetSafePosition;

			return SetSafePosition(Context, WorldContext, X, Y, nullptr);
		}

		void FLibrary::SetCenterOfViewportChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FSceneViewport* SV = ViewportLibrary::GetViewportChecked(Context, WorldContext);

			const FIntPoint Size = SV->GetSizeXY();

			SV->SetMouse(Size.X / 2, Size.Y / 2);
		}

		bool FLibrary::GetSafeDeprojectToWorld(const FString& Context, const UObject* WorldContext, FVector& OutWorldPosition, FVector& OutWorldDirection, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			FIntPoint Position;
			GetSafePosition(Context, WorldContext, Position, Log);

			if (Position == FIntPoint::NoneValue)
				return false;

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			return ViewportLibrary::SafeDeprojectScreenToWorld(Context, WorldContext, FVector2D(Position.X, Position.Y), OutWorldPosition, OutWorldDirection, Log);
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

		// Trace
		#pragma region

		#define ResponseType NCsTrace::NResponse::FResponse
		#define RequestType NCsTrace::NRequest::FRequest

		ResponseType* FLibrary::TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const float& Distance /*=1000000.0f*/)
		{
			FIntPoint Position;
			GetPositionChecked(Context, WorldContext, Position);

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			return ViewportLibrary::TraceChecked(Context, WorldContext, FVector2D(Position.X, Position.Y), Request, Distance);
		}

		ResponseType* FLibrary::SafeTrace(const FString& Context, const UObject* WorldContext, RequestType* Request, const float& Distance /*=1000000.0f*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			FIntPoint Position;
			if (!GetSafePosition(Context, WorldContext, Position, Log))
				return nullptr;

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			return ViewportLibrary::SafeTrace(Context, WorldContext, FVector2D(Position.X, Position.Y), Request, Distance, Log);
		}

		ResponseType* FLibrary::SafeTrace(const UObject* WorldContext, RequestType* Request, const float& Distance /*=1000000.0f*/)
		{
			using namespace NCsInput::NMouse::NLibrary::NCached;

			const FString& Context = Str::SafeTrace;

			return SafeTrace(Context, WorldContext, Request, Distance, nullptr);
		}

		#undef ResponseType
		#undef RequestType

		#pragma endregion Trace
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

	namespace NKey
	{
		bool FLibrary::IsValidForDevice(const FString& Context, const ECsInputDevice& Device, const FKey& Key, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_ENUM_VALID(EMCsInputDevice, ECsInputDevice, Device)

			if (!Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString())));
				return false;
			}

			// MouseAndKeyboard
			if (Device == ECsInputDevice::MouseAndKeyboard)
			{
				const bool bMouse = Key.IsMouseButton();
				const bool bKeyboard = !bMouse && !Key.IsGamepadKey() && !Key.IsTouch() && Key != EKeys::AnyKey;

				return bMouse || bKeyboard;
			}
			// Gamepad
			if (Device == ECsInputDevice::Gamepad)
			{
				return Key.IsGamepadKey();
			}
			// MotionController - TODO
			return false;
		}

		bool FLibrary::IsValidForMode(const FString& Context, const ECsInputMode& Mode, const FKey& Key, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (!Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString())));
				return false;
			}

			// Mouse - TODO: Add Mouse Axis
			if (Mode == ECsInputMode::Mouse)
				return Key.IsMouseButton();
			// Gamepad
			if (Mode == ECsInputMode::Gamepad)
				return Key.IsGamepadKey();
			// Touch
			if (Mode == ECsInputMode::Touch)
				return Key.IsTouch();
			// MotionController - TODO:
			return !Key.IsMouseButton() && !Key.IsGamepadKey() && !Key.IsTouch();
		}

		void FLibrary::GetChecked(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, TArray<FKey>& OutKeys)
		{
			check(EMCsInputAction::Get().IsValidEnumChecked(Context, Action));

			check(EMCsInputDevice::Get().IsValidEnumChecked(Context, Device));

			const FName& ActionName = Action.GetFName();

			UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();

			const TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->GetActionMappings();

			for (const FInputActionKeyMapping& Mapping : ActionMappings)
			{
				if (Mapping.ActionName == ActionName &&
					IsValidForDevice(Context, Device, Mapping.Key, nullptr))
				{
					OutKeys.Add(Mapping.Key);
				}
			}

			const TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->GetAxisMappings();

			for (const FInputAxisKeyMapping& Mapping : AxisMappings)
			{
				if (Mapping.AxisName == ActionName &&
					IsValidForDevice(Context, Device, Mapping.Key, nullptr))
				{
					OutKeys.Add(Mapping.Key);
				}
			}
			checkf(OutKeys.Num() > CS_EMPTY, TEXT("%s: Failed to find any keys associated with Action: %s for Device: %s."), *Context, Action.ToChar(), EMCsInputDevice::Get().ToChar(Device));
		}

		bool FLibrary::GetSafe(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, TArray<FKey>& OutKeys, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsInputAction, FECsInputAction, Action)

			CS_IS_ENUM_VALID(EMCsInputDevice, ECsInputDevice, Device)

			const FName& ActionName = Action.GetFName();

			UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();

			const TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->GetActionMappings();

			for (const FInputActionKeyMapping& Mapping : ActionMappings)
			{
				if (Mapping.ActionName == ActionName &&
					IsValidForDevice(Context, Device, Mapping.Key, nullptr))
				{
					OutKeys.Add(Mapping.Key);
				}
			}

			const TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->GetAxisMappings();

			for (const FInputAxisKeyMapping& Mapping : AxisMappings)
			{
				if (Mapping.AxisName == ActionName &&
					IsValidForDevice(Context, Device, Mapping.Key, nullptr))
				{
					OutKeys.Add(Mapping.Key);
				}
			}
			return OutKeys.Num() > CS_EMPTY;
		}

		FKey FLibrary::GetChecked(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device)
		{
			TArray<FKey> Keys;
			GetChecked(Context, Action, Device, Keys);

			checkf(Keys.Num() == 1, TEXT("%s: More than 1 %s: Key associated with Action: %s."), *Context, EMCsInputDevice::Get().ToChar(Device), Action.ToChar());
			return Keys[CS_FIRST];
		}

		FKey FLibrary::GetSafe(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			TArray<FKey> Keys;

			if (!GetSafe(Context, Action, Device, Keys, Log))
				return EKeys::Invalid;

			if (Keys.Num() > 1)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: More than 1 %s: Key associated with Action: %s."), *Context, EMCsInputDevice::Get().ToChar(Device), Action.ToChar()));
			}
			return Keys[CS_FIRST];
		}
	}

	namespace NMapping
	{
		bool FLibrary::IsValidChecked(const FString& Context, const FInputActionKeyMapping& Mapping)
		{
			CS_IS_NAME_NONE_CHECKED(Mapping.ActionName)

			checkf(Mapping.Key.IsValid(), TEXT("%s: Mapping.Key: %s is NOT Valid."), *Context, *(Mapping.Key.ToString()));
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const FInputActionKeyMapping& Mapping, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_NAME_NONE(Mapping.ActionName)

			if (!Mapping.Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mapping.Key: %s is NOT Valid."), *Context, *(Mapping.Key.ToString())));
				return false;
			}
			return true;
		}

		bool FLibrary::IsValidChecked(const FString& Context, const FInputAxisKeyMapping& Mapping)
		{
			CS_IS_NAME_NONE_CHECKED(Mapping.AxisName)

			checkf(Mapping.Key.IsValid(), TEXT("%s: Mapping.Key: %s is NOT Valid."), *Context, *(Mapping.Key.ToString()));

			CS_IS_FLOAT_NOT_EQUAL_CHECKED(Mapping.Scale, 0.0f)
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const FInputAxisKeyMapping& Mapping, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_NAME_NONE(Mapping.AxisName)

			if (!Mapping.Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mapping.Key: %s is NOT Valid."), *Context, *(Mapping.Key.ToString())));
				return false;
			}

			CS_IS_FLOAT_NOT_EQUAL(Mapping.Scale, 0.0f)
			return true;
		}

		// Add
		#pragma region

		void FLibrary::AddActionChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, const float& Scale /*=0.0f*/)
		{
			typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

			UPlayerInput* PlayerInput = PlayerInputLibrary::GetChecked(Context, WorldContext, ControllerId);

			check(EMCsInputAction::Get().IsValidEnumChecked(Context, Action));

			checkf(Key.IsValid(), TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString()));

			// NOTE: When creating a completely new Action, a Listener on Manager_Input will also need to be created.

			// NOTE: When changing a binding (NOT removing), call Add first and then remove the "old" mapping.

			const FName& ActionName = Action.GetFName();

			// Check Mapping already exists.

				// Action
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (ActionName == ActionMapping.ActionName &&
					Key == ActionMapping.Key)
				{
					checkf(0, TEXT("%s: Player: %d. ActionMapping already exists for Action: %s and Key: %s."), *Context, ControllerId, Action.ToChar(), *(Key.ToString()));
					return;
				}
			}
			// Axis
			for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
			{
				if (ActionName == AxisMapping.AxisName &&
					Key == AxisMapping.Key)
				{
					checkf(0, TEXT("%s: Player: %d. AxisMapping already exists for Action: %s and Key: %s."), *Context, ControllerId, Action.ToChar(), *(Key.ToString()));
					return;
				}
			}

			// Add Mapping

			// Check if the a mapping already exists for Action, if so add an ActionMapping
				// Action
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (ActionName == ActionMapping.ActionName)
				{
					FInputActionKeyMapping Mapping;
					Mapping.ActionName = ActionName;
					Mapping.Key = Key;

					PlayerInput->AddActionMapping(Mapping);
					return;
				}
			}

			// Check if the mapping already exists for Axis, if so add an AxisMapping
				// Axis
			for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
			{
				if (ActionName == AxisMapping.AxisName)
				{
					CS_IS_FLOAT_NOT_EQUAL_CHECKED(Scale, 0.0f)

					FInputAxisKeyMapping Mapping;
					Mapping.AxisName = ActionName;
					Mapping.Key = Key;
					Mapping.Scale = Scale;

					PlayerInput->AddAxisMapping(Mapping);
					return ;
				}
			}

			// Action
			if (Scale == 0.0f)
			{
				FInputActionKeyMapping Mapping;
				Mapping.ActionName = ActionName;
				Mapping.Key = Key;

				PlayerInput->AddActionMapping(Mapping);
			}
			// Axis
			else
			{
				FInputAxisKeyMapping Mapping;
				Mapping.AxisName = ActionName;
				Mapping.Key = Key;
				Mapping.Scale = Scale;

				PlayerInput->AddAxisMapping(Mapping);
			}
		}

		bool FLibrary::AddSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, const float& Scale /*=0.0f*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

			UPlayerInput* PlayerInput = PlayerInputLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

			if (!PlayerInput)
				return false;

			CS_IS_ENUM_STRUCT_VALID(EMCsInputAction, FECsInputAction, Action)

			if (!Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString())));
				return false;
			}

			// NOTE: When creating a completely new Action, a Listener on Manager_Input will also need to be created.

			// NOTE: When changing a binding (NOT removing), call Add first and then remove the "old" mapping.

			const FName& ActionName = Action.GetFName();

			// Check Mapping already exists.

				// Action
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (ActionName == ActionMapping.ActionName &&
					Key == ActionMapping.Key)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Player: %d. ActionMapping already exists for Action: %s and Key: %s."), *Context, ControllerId, Action.ToChar(), *(Key.ToString())));
					return false;
				}
			}
				// Axis
			for (FInputAxisKeyMapping& AxisMapping: PlayerInput->AxisMappings)
			{
				if (ActionName == AxisMapping.AxisName &&
					Key == AxisMapping.Key)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Player: %d. AxisMapping already exists for Action: %s and Key: %s."), *Context, ControllerId, Action.ToChar(), *(Key.ToString())));
					return false;
				}
			}

			// Add Mapping

			// Check if the a mapping already exists for Action, if so add an ActionMapping
				// Action
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (ActionName == ActionMapping.ActionName)
				{
					FInputActionKeyMapping Mapping;
					Mapping.ActionName = ActionName;
					Mapping.Key = Key;

					PlayerInput->AddActionMapping(Mapping);
					return true;
				}
			}

			// Check if the mapping already exists for Axis, if so add an AxisMapping
				// Axis
			for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
			{
				if (ActionName == AxisMapping.AxisName)
				{
					CS_IS_FLOAT_NOT_EQUAL(Scale, 0.0f)

					FInputAxisKeyMapping Mapping;
					Mapping.AxisName = ActionName;
					Mapping.Key = Key;
					Mapping.Scale = Scale;

					PlayerInput->AddAxisMapping(Mapping);
					return true;
				}
			}

			// Action
			if (Scale == 0.0f) 
			{
				FInputActionKeyMapping Mapping;
				Mapping.ActionName = ActionName;
				Mapping.Key = Key;

				PlayerInput->AddActionMapping(Mapping);
			}
			// Axis
			else
			{
				FInputAxisKeyMapping Mapping;
				Mapping.AxisName = ActionName;
				Mapping.Key = Key;
				Mapping.Scale = Scale;

				PlayerInput->AddAxisMapping(Mapping);
			}
			return true;
		}

		bool FLibrary::AddSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FInputActionKeyMapping& Mapping, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

			UPlayerInput* PlayerInput = PlayerInputLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

			if (!PlayerInput)
				return false;

			if (!IsValid(Context, Mapping, Log))
				return false;

			// Check Mapping already exists.
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (Mapping.ActionName == ActionMapping.ActionName &&
					Mapping.Key == ActionMapping.Key)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Player: %d. ActionMapping already exists for Mapping.ActionName: %s and Mapping.Key: %s."), *Context, ControllerId, *(Mapping.ActionName.ToString()), *(Mapping.Key.ToString())));
					return false;
				}
			}

			PlayerInput->AddActionMapping(Mapping);
			return true;
		}

		bool FLibrary::AddSafeAxis(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FInputAxisKeyMapping& Mapping, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

			UPlayerInput* PlayerInput = PlayerInputLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

			if (!PlayerInput)
				return false;

			if (!IsValid(Context, Mapping, Log))
				return false;

			// Check Mapping already exists.
			for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
			{
				if (Mapping.AxisName == AxisMapping.AxisName &&
					Mapping.Key == AxisMapping.Key)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Player: %d. AxisMapping already exists for Mapping.AxisName: %s and Mapping.Key: %s."), *Context, ControllerId, *(Mapping.AxisName.ToString()), *(Mapping.Key.ToString())));
					return false;
				}
			}

			PlayerInput->AddAxisMapping(Mapping);
			return true;
		}

		#pragma endregion Add

		// Remove
		#pragma region

		void FLibrary::RemoveActionChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key)
		{
			typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

			UPlayerInput* PlayerInput = PlayerInputLibrary::GetChecked(Context, WorldContext, ControllerId);

			check(EMCsInputAction::Get().IsValidEnumChecked(Context, Action));

			checkf(Key.IsValid(), TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString()));

			// NOTE: When creating a completely new Action, a Listener on Manager_Input will also need to be created.

			// NOTE: When changing a binding (NOT removing), call Add first and then remove the "old" mapping.

			const FName& ActionName = Action.GetFName();

			// Find the remove the mapping

				// Action
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (ActionName == ActionMapping.ActionName &&
					Key == ActionMapping.Key)
				{
					PlayerInput->RemoveActionMapping(ActionMapping);
					return;
				}
			}
				// Axis
			for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
			{
				if (ActionName == AxisMapping.AxisName &&
					Key == AxisMapping.Key)
				{
					PlayerInput->RemoveAxisMapping(AxisMapping);
					return;
				}
			}
		}

		bool FLibrary::RemoveSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

			UPlayerInput* PlayerInput = PlayerInputLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

			if (!PlayerInput)
				return false;

			CS_IS_ENUM_STRUCT_VALID(EMCsInputAction, FECsInputAction, Action)

			if (!Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString())));
				return false;
			}

			// NOTE: When creating a completely new Action, a Listener on Manager_Input will also need to be created.

			// NOTE: When changing a binding (NOT removing), call Add first and then remove the "old" mapping.

			const FName& ActionName = Action.GetFName();

			// Find the remove the mapping

				// Action
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (ActionName == ActionMapping.ActionName &&
					Key == ActionMapping.Key)
				{
					PlayerInput->RemoveActionMapping(ActionMapping);
					return true;
				}
			}
				// Axis
			for (FInputAxisKeyMapping& AxisMapping: PlayerInput->AxisMappings)
			{
				if (ActionName == AxisMapping.AxisName &&
					Key == AxisMapping.Key)
				{
					PlayerInput->RemoveAxisMapping(AxisMapping);
					return true;
				}
			}
			return false;
		}

		#pragma endregion Remove

		// Replace
		#pragma region

		void FLibrary::ReplaceActionChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key, const float& Scale /*=0.0f*/)
		{
			typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

			UPlayerInput* PlayerInput = PlayerInputLibrary::GetChecked(Context, WorldContext, ControllerId);

			check(EMCsInputDevice::Get().IsValidEnumChecked(Context, Device));

			check(EMCsInputAction::Get().IsValidEnumChecked(Context, Action));

			checkf(Key.IsValid(), TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString()));

			checkf(NCsInput::NKey::FLibrary::IsValidForDevice(Context, Device, Key), TEXT("%s: Key: %s is NOT Valid for Device: %s."), *Context, *(Key.ToString()), *(EMCsInputDevice::Get().ToChar(Device)));

			const FName& ActionName = Action.GetFName();

			// Check Mapping already exists.

				// Action
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (ActionName == ActionMapping.ActionName &&
					Key == ActionMapping.Key)
				{
					return;
				}
			}
			// Axis
			for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
			{
				if (ActionName == AxisMapping.AxisName &&
					Key == AxisMapping.Key)
				{
					return;
				}
			}

			// Add the Mapping

				// Action
			if (Scale == 0.0f)
			{
				FInputActionKeyMapping Mapping;
				Mapping.ActionName = ActionName;
				Mapping.Key = Key;

				PlayerInput->AddActionMapping(Mapping);
			}
			// Axis
			else
			{
				FInputAxisKeyMapping Mapping;
				Mapping.AxisName = ActionName;
				Mapping.Key = Key;
				Mapping.Scale = Scale;

				PlayerInput->AddAxisMapping(Mapping);
			}

			// Remove the any mappings that are Key's for Device (excluding the Key that was added)

				// Action
			if (Scale == 0.0f)
			{
				TArray<FInputActionKeyMapping> Mappings;

				for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
				{
					if (ActionName == ActionMapping.ActionName &&
						Key != ActionMapping.Key &&
						NCsInput::NKey::FLibrary::IsValidForDevice(Context, Device, ActionMapping.Key, nullptr))
					{
						Mappings.Add(ActionMapping);
					}
				}

				for (FInputActionKeyMapping& Mapping : Mappings)
				{
					PlayerInput->RemoveActionMapping(Mapping);
				}
			}
			// Axis
			else
			{
				TArray<FInputAxisKeyMapping> Mappings;

				for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
				{
					if (ActionName == AxisMapping.AxisName &&
						Key != AxisMapping.Key &&
						NCsInput::NKey::FLibrary::IsValidForDevice(Context, Device, AxisMapping.Key, nullptr))
					{
						Mappings.Add(AxisMapping);
					}
				}

				for (FInputAxisKeyMapping& Mapping : Mappings)
				{
					PlayerInput->RemoveAxisMapping(Mapping);
				}
			}
		}

		bool FLibrary::SafeReplaceAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key, const float& Scale /*=0.0f*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsPlayer::NInput::FLibrary PlayerInputLibrary;

			UPlayerInput* PlayerInput = PlayerInputLibrary::GetSafe(Context, WorldContext, ControllerId, Log);

			if (!PlayerInput)
				return false;

			CS_IS_ENUM_VALID(EMCsInputDevice, ECsInputDevice, Device)

			CS_IS_ENUM_STRUCT_VALID(EMCsInputAction, FECsInputAction, Action)

			if (!Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString())));
				return false;
			}

			if (!NCsInput::NKey::FLibrary::IsValidForDevice(Context, Device, Key))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid for Device: %s."), *Context, *(Key.ToString()), *(EMCsInputDevice::Get().ToChar(Device))));
				return false;
			}

			const FName& ActionName = Action.GetFName();

			// Check Mapping already exists.
			
				// Action
			for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
			{
				if (ActionName == ActionMapping.ActionName &&
					Key == ActionMapping.Key)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Player: %d. ActionMapping already exists for Action: %s and Key: %s."), *Context, ControllerId, Action.ToChar(), *(Key.ToString())));
					return true;
				}
			}
				// Axis
			for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
			{
				if (ActionName == AxisMapping.AxisName &&
					Key == AxisMapping.Key)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Player: %d. AxisMapping already exists for Action: %s and Key: %s."), *Context, ControllerId, Action.ToChar(), *(Key.ToString())));
					return true;
				}
			}

			// Add the Mapping

				// Action
			if (Scale == 0.0f)
			{
				FInputActionKeyMapping Mapping;
				Mapping.ActionName = ActionName;
				Mapping.Key = Key;

				PlayerInput->AddActionMapping(Mapping);
			}
				// Axis
			else
			{
				FInputAxisKeyMapping Mapping;
				Mapping.AxisName = ActionName;
				Mapping.Key = Key;
				Mapping.Scale = Scale;

				PlayerInput->AddAxisMapping(Mapping);
			}

			// Remove the any mappings that are Key's for Device (excluding the Key that was added)

				// Action
			if (Scale == 0.0f)
			{
				TArray<FInputActionKeyMapping> Mappings;

				for (FInputActionKeyMapping& ActionMapping : PlayerInput->ActionMappings)
				{
					if (ActionName == ActionMapping.ActionName &&
						Key != ActionMapping.Key &&
						NCsInput::NKey::FLibrary::IsValidForDevice(Context, Device, ActionMapping.Key, nullptr))
					{
						Mappings.Add(ActionMapping);
					}
				}

				for (FInputActionKeyMapping& Mapping : Mappings)
				{
					PlayerInput->RemoveActionMapping(Mapping);
				}
			}
				// Axis
			else
			{
				TArray<FInputAxisKeyMapping> Mappings;

				for (FInputAxisKeyMapping& AxisMapping : PlayerInput->AxisMappings)
				{
					if (ActionName == AxisMapping.AxisName &&
						Key != AxisMapping.Key &&
						NCsInput::NKey::FLibrary::IsValidForDevice(Context, Device, AxisMapping.Key, nullptr))
					{
						Mappings.Add(AxisMapping);
					}
				}

				for (FInputAxisKeyMapping& Mapping : Mappings)
				{
					PlayerInput->RemoveAxisMapping(Mapping);
				}
			}
			return true;
		}

		#pragma endregion Replace
	}

	namespace NAction
	{
		const FECsInputAction& FLibrary::GetChecked(const FString& Context, const FKey& Key)
		{
			checkf(Key.IsValid(), TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString()));

			UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();

			// Check Action Mapping
			const TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->GetActionMappings();

			for (const FInputActionKeyMapping& Mapping : ActionMappings)
			{
				if (Mapping.Key == Key)
					return EMCsInputAction::Get().GetEnum(Mapping.ActionName);
			}
			// Check Axis Mapping
			const TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->GetAxisMappings();

			for (const FInputAxisKeyMapping& Mapping : AxisMappings)
			{
				if (Mapping.Key == Key)
					return EMCsInputAction::Get().GetEnum(Mapping.AxisName);
			}
			return EMCsInputAction::Get().GetMAX();
		}

		const FECsInputAction& FLibrary::GetSafe(const FString& Context, const FKey& Key, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (!Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString())));
				return EMCsInputAction::Get().GetMAX();
			}

			UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();

			// Check Action Mapping
			const TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->GetActionMappings();

			for (const FInputActionKeyMapping& Mapping : ActionMappings)
			{
				if (Mapping.Key == Key)
					return EMCsInputAction::Get().GetEnum(Mapping.ActionName);
			}
			// Check Axis Mapping
			const TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->GetAxisMappings();

			for (const FInputAxisKeyMapping& Mapping : AxisMappings)
			{
				if (Mapping.Key == Key)
					return EMCsInputAction::Get().GetEnum(Mapping.AxisName);
			}
			return EMCsInputAction::Get().GetMAX();
		}
		
		bool FLibrary::IsAssociatedWithChecked(const FString& Context, const FECsInputAction& Action, const FKey& Key)
		{
			check(EMCsInputAction::Get().IsValidEnumChecked(Context, Action));

			checkf(Key.IsValid(), TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString()));

			UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();

			const FName& ActionName = Action.GetFName();

			// Check Action Mapping
			const TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->GetActionMappings();

			for (const FInputActionKeyMapping& Mapping : ActionMappings)
			{
				if (Mapping.ActionName == ActionName &&
					Mapping.Key == Key)

				{
					return true;
				}
			}
			// Check Axis Mapping
			const TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->GetAxisMappings();

			for (const FInputAxisKeyMapping& Mapping : AxisMappings)
			{
				if (Mapping.AxisName == ActionName &&
					Mapping.Key == Key)

				{
					return true;
				}
			}
			return false;
		}

		bool FLibrary::SafeIsAssociatedWith(const FString& Context, const FECsInputAction& Action, const FKey& Key, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsInputAction, FECsInputAction, Action)

			if (!Key.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString())));
				return false;
			}

			UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();

			const FName& ActionName = Action.GetFName();

			// Check Action Mapping
			const TArray<FInputActionKeyMapping>& ActionMappings = InputSettings->GetActionMappings();

			for (const FInputActionKeyMapping& Mapping : ActionMappings)
			{
				if (Mapping.ActionName == ActionName &&
					Mapping.Key == Key)

				{
					return true;
				}
			}
			// Check Axis Mapping
			const TArray<FInputAxisKeyMapping>& AxisMappings = InputSettings->GetAxisMappings();

			for (const FInputAxisKeyMapping& Mapping : AxisMappings)
			{
				if (Mapping.AxisName == ActionName &&
					Mapping.Key == Key)

				{
					return true;
				}
			}
			return false;
		}
	}
}