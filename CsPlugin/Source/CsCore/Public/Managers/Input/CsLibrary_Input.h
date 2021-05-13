// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "InputCoreTypes.h"
// Log
#include "Utility/CsLog.h"

class UObject;

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
			* @param Log
			*/
			static void GetSafePosition(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the current mouse position in viewport space.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutPosition	(out)
			*/
			static void GetSafePosition(const UObject* WorldContext, FIntPoint& OutPosition);

			/**
			* Set the mouse position in viewport space.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param X
			* @param Y
			*/
			static void SetPositionChecked(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y);

			/**
			* Safely set the mouse position in viewport space.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param X
			* @param Y
			* @param Log
			*/
			static void SetSafePosition(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely set the mouse position in viewport space.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param X
			* @param Y
			*/
			static void SetSafePosition(const UObject* WorldContext, const int32& X, const int32& Y);

			/**
			* Set the mouse position to the center of the viewport.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void SetCenterOfViewportChecked(const FString& Context, const UObject* WorldContext);

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
}