// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CoreMinimal.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;

namespace NCsInput
{
	namespace NMouse
	{
		struct CSCORELIBRARY_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

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
			* @param Log			(optional)
			* return				Whether or not the cursor is being shown.
			*/
			static bool SafeIsShowingCursor(const FString& Context, const UObject* WorldContext, LogLevel);
			FORCEINLINE static bool SafeIsShowingCursor(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SafeIsShowingCursor(Context, WorldContext, Log);
				return OutSuccess;
			}

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
			* @param Log			(optional)
			* return
			*/
			static bool SafeShowCursor(const FString& Context, const UObject* WorldContext, LogLevel);
			FORCEINLINE static bool SafeShowCursor(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SafeShowCursor(Context, WorldContext, Log);
				return OutSuccess;
			}

			/**
			* Safely show the mouse cursor. This sets bShowMouseCursor = true for the
			* First Local Player Controller.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static bool SafeShowCursor(const UObject* WorldContext);

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
			* @param Log			(optional)
			* return
			*/
			static bool SafeHideCursor(const FString& Context, const UObject* WorldContext, LogLevel);
			FORCEINLINE static bool SafeHideCursor(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SafeHideCursor(Context, WorldContext, Log);
				return OutSuccess;
			}

			/**
			* Safely hide the mouse cursor. This sets bShowMouseCursor = false for the
			* Fist Local Player Controller.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static bool SafeHideCursor(const UObject* WorldContext);

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
			static bool GetSafePosition(const FString& Context, const UObject* WorldContext, FIntPoint& OutPosition, LogLevel);

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
			static bool SetSafePosition(const FString& Context, const UObject* WorldContext, const int32& X, const int32& Y, LogLevel);

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
			static bool SetSafeCenterOfViewport(const FString& Context, const UObject* WorldContext, LogLevel);

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
			static bool GetSafeDeprojectToWorld(const FString& Context, const UObject* WorldContext, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection, LogLevel);

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
			* Safely Refresh the mouse position.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static bool SafeRefreshPosition(const FString& Context, const UObject* WorldContext, LogLevel);
			FORCEINLINE static bool SafeRefreshPosition(const FString& Context, const UObject* WorldContext, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SafeRefreshPosition(Context, WorldContext, Log);
				return OutSuccess;
			}

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
			static bool GetWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FPlane4f& Plane, FVector3f& OutIntersection);

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
			static bool GetSafeWorldIntersection(const FString& Context, const UObject* WorldContext, const FPlane4f& Plane, FVector3f& OutIntersection, LogLevel);

			/**
			* Safely get the intersection between the de-projection of the current mouse position (viewport space) to a world ray (location and direction)
			* with a world plane (location and normal).
			*
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param Plane				Location and normal in World Space.
			* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
			* return					Whether the intersection exists or not.
			*/
			static bool GetSafeWorldIntersection(const UObject* WorldContext, const FPlane4f& Plane, FVector3f& OutIntersection);

		#undef LogLevel
		};
	}
}