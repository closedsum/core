// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "InputCoreTypes.h"
#include "Managers/Input/CsTypes_Input.h"
// Input
#include "GameFramework/PlayerInput.h"
#include "Managers/Input/Action/CsInputAction.h"
// Log
#include "Utility/CsLog.h"

class UObject;

// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)
// NCsTrace::NResponse::FResponse
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)

namespace NCsInput
{
	namespace NMouse
	{
		struct CSCORE_API FLibrary final
		{
		// Show / Hide
		#pragma region
		public:

			/**
			* Check if the mouse cursor is being shown. This checks bShowMouseCursor == true
			* for the First Local Player Controller.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Whether or not the cursor is being shown.
			*/
			static bool IsShowingCursorChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely check if the mouse cursor is being shown. This checks bShowMouseCursor == true
			* for the First Local Player Controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Whether or not the cursor is being shown.
			*/
			static bool SafeIsShowingCursor(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely check if the mouse cursor is being shown. This checks bShowMouseCursor == true
			* for the First Local Player Controller.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Whether or not the cursor is being shown.
			*/
			static bool SafeIsShowingCursor(const UObject* WorldContext);

			/**
			* Show the mouse cursor. This sets bShowMouseCursor = true for the
			* First Local Player Controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void ShowCursorChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely show the mouse cursor. This sets bShowMouseCursor = true for the
			* First Local Player Controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			*/
			static void SafeShowCursor(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely show the mouse cursor. This sets bShowMouseCursor = true for the
			* First Local Player Controller.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void SafeShowCursor(const UObject* WorldContext);

			/**
			* Hide the mouse cursor. This sets bShowMouseCursor = false for the 
			* Fist Local Player Controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void HideCursorChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely hide the mouse cursor. This sets bShowMouseCursor = false for the
			* Fist Local Player Controller.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			*/
			static void SafeHideCursor(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely hide the mouse cursor. This sets bShowMouseCursor = false for the
			* Fist Local Player Controller.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void SafeHideCursor(const UObject* WorldContext);

		#pragma endregion Show / Hide

		// Get / Set
		#pragma region
		public:

			/**
			* Get the current mouse position in viewport space.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutPosition	(out)
			*/
			static void GetPositionChecked(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition);

			/**
			* Safely get the current mouse position in viewport space.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutPosition	(out)
			* @param Log			(optional)
			* return				Whether current mouse position was obtained successfully.
			*/
			static bool GetSafePosition(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the current mouse position in viewport space.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutPosition	(out)
			* return				Whether current mouse position was obtained successfully.
			*/
			static bool GetSafePosition(const UObject* WorldContext, FIntPoint& OutPosition);

			/**
			* Set the mouse position in viewport space.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param X				X screen position (viewport space).
			* @param Y				Y screen position (viewport space).
			*/
			static void SetPositionChecked(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y);

			/**
			* Safely set the mouse position in viewport space.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param X				X screen position (viewport space).
			* @param Y				Y screen position (viewport space).
			* @param Log			(optional)
			* return				Whether current mouse position was obtained successfully.
			*/
			static bool SetSafePosition(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the mouse position in viewport space.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param X				X screen position (viewport space).
			* @param Y				Y screen position (viewport space).
			* return				Whether current mouse position was obtained successfully.
			*/
			static bool SetSafePosition(const UObject* WorldContext, const int32& X, const int32& Y);

			/**
			* Set the mouse position to the center of the viewport.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void SetCenterOfViewportChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely set the mouse position to the center of the viewport.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				Whether the mouse position was set to the center of the viewport or not.
			*/
			static bool SetSafeCenterOfViewport(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely convert the current mouse position in viewport space into a 3D world-space point and direction.
			* 
			* @param Context			The calling context.
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutWorldPosition	(out)
			* @param OutWorldDirection	(out)
			* @parma Log				(optional)
			* return					Whether the deproject was successful or not.
			*/
			static bool GetSafeDeprojectToWorld(const FString& Context, const UObject* WorldContext, FVector& OutWorldPosition, FVector& OutWorldDirection, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Get / Set

		public:

			/**
			* Refresh the mouse position.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void RefreshPositionChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Get the intersection between the de-projection of the current mouse position (viewport space) to a world ray (location and direction)
			* with a world plane (location and normal).
			*
			* @param Context			The calling context.
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param Plane				Location and normal in World Space.
			* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
			* return					Whether the intersection exists or not.
			*/
			static bool GetWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FPlane& Plane, FVector& OutIntersection);

			/**
			* Safely get the intersection between the de-projection of the current mouse position (viewport space) to a world ray (location and direction)
			* with a world plane (location and normal).
			*
			* @param Context			The calling context.
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param Plane				Location and normal in World Space.
			* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
			* @param Log
			* return					Whether the intersection exists or not.
			*/
			static bool GetSafeWorldIntersection(const FString& Context, const UObject* WorldContext, const FPlane& Plane, FVector& OutIntersection, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the intersection between the de-projection of the current mouse position (viewport space) to a world ray (location and direction)
			* with a world plane (location and normal).
			*
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param Plane				Location and normal in World Space.
			* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
			* return					Whether the intersection exists or not.
			*/
			static bool GetSafeWorldIntersection(const UObject* WorldContext, const FPlane& Plane, FVector& OutIntersection);

		// Trace
		#pragma region
		public:

		#define ResponseType NCsTrace::NResponse::FResponse
		#define RequestType NCsTrace::NRequest::FRequest

			/**
			* Perform a trace with the given Request.
			*  Request->Start is replaced by:
			*   de-projection of the current mouse position (viewport space)
			*  Request->End is replaced by:
			*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Request
			* @param Distance		(optional) The distance to project outward from the Request->Start.
			* return				Response
			*/
			static ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, RequestType* Request, const float& Distance = 1000000.0f);

			/**
			* Safely perform a trace with the given Request.
			*  Request->Start is replaced by:
			*   de-projection of the current mouse position (viewport space)
			*  Request->End is replaced by:
			*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Request
			* @param Distance		(optional) The distance to project outward from the Request->Start.
			* @param Log			(optional)
			* return				Response
			*/
			static ResponseType* SafeTrace(const FString& Context, const UObject* WorldContext, RequestType* Request, const float& Distance = 1000000.0f, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely perform a trace with the given Request.
			*  Request->Start is replaced by:
			*   de-projection of the current mouse position (viewport space)
			*  Request->End is replaced by:
			*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Request
			* @param Distance		(optional) The distance to project outward from the Request->Start.
			* return				Response
			*/
			static ResponseType* SafeTrace(const UObject* WorldContext, RequestType* Request, const float& Distance = 1000000.0f);

		#undef ResponseType
		#undef RequestType

		#pragma endregion Trace
		};
	}

	namespace NTouch
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			*
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param FingerIndex
			* @param OutPosition	(out)
			*/
			static bool GetPositionChecked(const FString& Context, const UObject* WorldContext, const ETouchIndex::Type& FingerIndex, FIntPoint& OutPosition);
		};
	}

	namespace NKey
	{
		struct CSCORE_API FLibrary final
		{
		public:

			static bool IsValidForDevice(const FString& Context, const ECsInputDevice& Device, const FKey& Key, void(*Log)(const FString&) = &FCsLog::Warning);

			static bool IsValidForMode(const FString& Context, const ECsInputMode& Mode, const FKey& Key, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static bool GetSafe(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, TArray<FKey>& OutKeys, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static FKey GetSafe(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, void(*Log)(const FString&) = &FCsLog::Warning);
		};
	}

	namespace NMapping
	{
		struct CSCORE_API FLibrary final
		{
		public:

			static bool IsValidChecked(const FString& Context, const FInputActionKeyMapping& Mapping);

			static bool IsValid(const FString& Context, const FInputActionKeyMapping& Mapping, void(*Log)(const FString&) = &FCsLog::Warning);

			static bool IsValidChecked(const FString& Context, const FInputAxisKeyMapping& Mapping);

			static bool IsValid(const FString& Context, const FInputAxisKeyMapping& Mapping, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static bool AddSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, const float& Scale = 0.0f, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely add a FInputActionKeyMapping for the PlayerInput associated with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Mapping
			* @param Log			(optional)
			* return				Whether a mapping was successfully added.
			*/
			static bool AddSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FInputActionKeyMapping& Mapping, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely add a FInputAxisKeyMapping for the PlayerInput associated with ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Mapping
			* @param Log			(optional)
			* return				Whether a mapping was successfully added.
			*/
			static bool AddSafeAxis(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FInputAxisKeyMapping& Mapping, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static bool RemoveSafeAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const FECsInputAction& Action, const FKey& Key, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static bool SafeReplaceAction(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key, const float& Scale = 0.0f, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Replace
		};
	}

	namespace NAction
	{
		struct CSCORE_API FLibrary final
		{
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
			static const FECsInputAction& GetSafe(const FString& Context, const FKey& Key, void(*Log)(const FString&) = &FCsLog::Warning);

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
			static bool SafeIsAssociatedWith(const FString& Context, const FECsInputAction& Action, const FKey& Key, void(*Log)(const FString&) = &FCsLog::Warning);
		};
	}
}