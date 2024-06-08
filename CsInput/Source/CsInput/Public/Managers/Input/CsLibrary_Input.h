// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "InputCoreTypes.h"
#include "Managers/Input/CsTypes_Input.h"
// Input
#include "GameFramework/PlayerInput.h"
#include "Managers/Input/Action/CsInputAction.h"
// Log
#include "Utility/CsInputLog.h"

class UObject;

namespace NCsInput
{
	namespace NKey
	{
		struct CSINPUT_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsInput::FLog::Warning

		public:

			static bool IsValidForDevice(const FString& Context, const ECsInputDevice& Device, const FKey& Key, LogLevel);

			static bool IsValidForMode(const FString& Context, const ECsInputMode& Mode, const FKey& Key, LogLevel);

			/**
			* Get the Keys for Device associated with Action.
			*
			* @param Context	The calling context.
			* @param Action
			* @param Device
			* @param OutKeys	(out)
			*/
			static void GetChecked(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, TArray<FKey>& OutKeys);

			/**
			* Safely get the Keys for Device associated with Action.
			* 
			* @param Context	The calling context.
			* @param Action
			* @param Device
			* @param OutKeys	(out)
			* @param Log		(optional)
			* return			Whether any keys for Device are associated with Action.
			*/
			static bool GetSafe(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, TArray<FKey>& OutKeys, LogLevel);

			/**
			* Get the Key for Device associated with Action.
			* NOTE: If there is MORE than ONE Key, this will assert.
			*
			* @param Context	The calling context
			* @param Action
			* @param Device
			* return			Key for Device associated with Action.
			*/
			static FKey GetChecked(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device);

			/**
			* Safely get the Key for Device associated with Action.
			* NOTE: If there is MORE than ONE Key, return the FIRST Key.
			* 
			* @param Context	The calling context
			* @param Action
			* @param Device
			* @param Log		(optional)
			* return			Key for Device associated with Action.
			*/
			static FKey GetSafe(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, LogLevel);

		#undef LogLevel
		};
	}

	namespace NMapping
	{
		struct CSINPUT_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsInput::FLog::Warning

		public:

			static bool IsValidChecked(const FString& Context, const FInputActionKeyMapping& Mapping);

			static bool IsValid(const FString& Context, const FInputActionKeyMapping& Mapping, LogLevel);

			static bool IsValidChecked(const FString& Context, const FInputAxisKeyMapping& Mapping);

			static bool IsValid(const FString& Context, const FInputAxisKeyMapping& Mapping, LogLevel);

		// Add
		#pragma region
		public:

			/**
			* Add a Mapping (FInputActionKeyMapping or FInputAxisKeyMapping) with name: Action.GetFName() and Key for
			* the PlayerInput associated with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Action
			* @param Key
			* @param Scale			Only relevant if the Action is of type Axis.
			*/
			static void AddActionChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, const float& Scale = 0.0f);

			/**
			* Safely add a Mapping (FInputActionKeyMapping or FInputAxisKeyMapping) with name: Action.GetFName() and Key for
			* the PlayerInput associated with ControllerId.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Action
			* @param Key
			* @param Scale			Only relevant if the Action is of type Axis.
			* @param Log			(optional)
			* return				Whether a mapping was successfully added.
			*/
			static bool AddSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, const float& Scale = 0.0f, LogLevel);

			/**
			* Safely add a FInputActionKeyMapping for the PlayerInput associated with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Mapping
			* @param Log			(optional)
			* return				Whether a mapping was successfully added.
			*/
			static bool AddSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FInputActionKeyMapping& Mapping, LogLevel);

			/**
			* Safely add a FInputAxisKeyMapping for the PlayerInput associated with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Mapping
			* @param Log			(optional)
			* return				Whether a mapping was successfully added.
			*/
			static bool AddSafeAxis(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FInputAxisKeyMapping& Mapping, LogLevel);

		#pragma endregion Add

		// Remove
		#pragma region
		public:

			/**
			* Remove a Mapping (FInputActionKeyMapping or FInputAxisKeyMapping) with name: Action.GetFName() and Key for
			* the PlayerInput associated with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Action
			* @param Key
			*/
			static void RemoveActionChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key);

			/**
			* Safely remove a Mapping (FInputActionKeyMapping or FInputAxisKeyMapping) with name: Action.GetFName() and Key for
			* the PlayerInput associated with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Action
			* @param Key
			* @param Log			(optional)
			* return				Whether a mapping was successfully added.
			*/
			static bool RemoveSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, LogLevel);

		#pragma endregion Remove

		// Replace
		#pragma region

			/**
			* Replace a Mapping (FInputActionKeyMapping or FInputAxisKeyMapping) with name: Action.GetFName() and Key for
			* the PlayerInput associated with ControllerId.
			* NOTE: Assumes there is only ONE Key associated with the Device (i.e. there is only ONE Mouse, Keyboard, Gamepad, ... etc Key).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Device
			* @param Action
			* @param Key
			* @param Scale			Only relevant if the Action is of type Axis.
			*/
			static void ReplaceActionChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key, const float& Scale = 0.0f);

			/**
			* Safely replace a Mapping (FInputActionKeyMapping or FInputAxisKeyMapping) with name: Action.GetFName() and Key for
			* the PlayerInput associated with ControllerId.
			* NOTE: Assumes there is only ONE Key associated with the Device (i.e. there is only ONE Mouse, Keyboard, Gamepad, ... etc Key).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Device		
			* @param Action
			* @param Key
			* @param Scale			Only relevant if the Action is of type Axis.
			* @param Log			(optional)
			* return				Whether a mapping was successfully added.
			*/
			static bool SafeReplaceAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key, const float& Scale = 0.0f, LogLevel);

		#pragma endregion Replace

		#undef LogLevel
		};
	}

	namespace NAction
	{
		struct CSINPUT_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsInput::FLog::Warning

		public:

			/**
			* Get a InputAction by Key. 
			* This looks at the InputSettings for any Action that has Key associated with it.
			* 
			* @param Context	The calling context.
			* @param Key
			* return			Input Action.
			*/
			static const FECsInputAction& GetChecked(const FString& Context, const FKey& Key);

			/**
			* Safely get a InputAction by Key.
			* This looks at the InputSettings for any Action that has Key associated with it.
			*
			* @param Context	The calling context.
			* @param Key
			* @param Log		(optional)
			* return			Input Action.
			*/
			static const FECsInputAction& GetSafe(const FString& Context, const FKey& Key, LogLevel);

			/**
			* Check if the Action is associated with the Key.
			* This looks at InputSettings.
			* 
			* @param Context	The calling context.
			* @param Action
			* @param Key
			* return			Whether the Action is associated with the Key or not.
			*/
			static bool IsAssociatedWithChecked(const FString& Context, const FECsInputAction& Action, const FKey& Key);

			/**
			* Safely check if the Action is associated with the Key.
			* This looks at InputSettings.
			*
			* @param Context	The calling context.
			* @param Action
			* @param Key
			* @param Log		(optional)
			* return			Whether the Action is associated with the Key or not.
			*/
			static bool SafeIsAssociatedWith(const FString& Context, const FECsInputAction& Action, const FKey& Key, LogLevel);

		#undef LogLevel
		};
	}
}