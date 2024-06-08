// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsLibrary_Input.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "GameFramework/InputSettings.h"

namespace NCsInput
{
	namespace NKey
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsInput::FLog::Warning*/

		bool FLibrary::IsValidForDevice(const FString& Context, const ECsInputDevice& Device, const FKey& Key, LogLevel)
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

		bool FLibrary::IsValidForMode(const FString& Context, const ECsInputMode& Mode, const FKey& Key, LogLevel)
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
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsInputAction, Action)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsInputDevice, Device)

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

		bool FLibrary::GetSafe(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, TArray<FKey>& OutKeys, LogLevel)
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

		FKey FLibrary::GetSafe(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, LogLevel)
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

		#undef LogLevel
	}

	namespace NMapping
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsInput::FLog::Warning*/
		#define PlayerInputLibrary NCsPlayer::NInput::FLibrary

		bool FLibrary::IsValidChecked(const FString& Context, const FInputActionKeyMapping& Mapping)
		{
			CS_IS_NAME_NONE_CHECKED(Mapping.ActionName)

			checkf(Mapping.Key.IsValid(), TEXT("%s: Mapping.Key: %s is NOT Valid."), *Context, *(Mapping.Key.ToString()));
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const FInputActionKeyMapping& Mapping, LogLevel)
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

		bool FLibrary::IsValid(const FString& Context, const FInputAxisKeyMapping& Mapping, LogLevel)
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
			UPlayerInput* PlayerInput = PlayerInputLibrary::GetChecked(Context, WorldContext, ControllerId);

			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsInputAction, Action)
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

		bool FLibrary::AddSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, const float& Scale /*=0.0f*/, LogLevel)
		{
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

		bool FLibrary::AddSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FInputActionKeyMapping& Mapping, LogLevel)
		{
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

		bool FLibrary::AddSafeAxis(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FInputAxisKeyMapping& Mapping, LogLevel)
		{
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
			UPlayerInput* PlayerInput = PlayerInputLibrary::GetChecked(Context, WorldContext, ControllerId);

			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsInputAction, Action)
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

		bool FLibrary::RemoveSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, LogLevel)
		{
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
			UPlayerInput* PlayerInput = PlayerInputLibrary::GetChecked(Context, WorldContext, ControllerId);

			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsInputDevice, Device)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsInputAction, Action)
			checkf(Key.IsValid(), TEXT("%s: Key: %s is NOT Valid."), *Context, *(Key.ToString()));
			checkf(NCsInput::NKey::FLibrary::IsValidForDevice(Context, Device, Key), TEXT("%s: Key: %s is NOT Valid for Device: %s."), *Context, *(Key.ToString()), EMCsInputDevice::Get().ToChar(Device));

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

		bool FLibrary::SafeReplaceAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key, const float& Scale /*=0.0f*/, LogLevel)
		{
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

		#undef LogLevel
		#undef PlayerInputLibrary
	}

	namespace NAction
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsInput::FLog::Warning*/

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

		const FECsInputAction& FLibrary::GetSafe(const FString& Context, const FKey& Key, LogLevel)
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

		bool FLibrary::SafeIsAssociatedWith(const FString& Context, const FECsInputAction& Action, const FKey& Key, LogLevel)
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

		#undef LogLevel
	}
}