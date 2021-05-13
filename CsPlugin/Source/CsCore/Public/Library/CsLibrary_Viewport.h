// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class FSceneViewport;

namespace NCsViewport
{
	namespace NLocal
	{
		namespace NPlayer
		{
			class CSCORE_API FLibrary
			{
			public:

				/**
				* Check whether the First Local Player's Viewport can project a world location to a screen
				* position.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Whether the projection is possible or not.
				*/
				static bool CanProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Safely check whether the First Local Player's Viewport can project a world location to a screen
				* position.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Log
				* return				Whether the projection is possible or not.
				*/
				static bool CanSafeProjectWorldToScreen(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely check whether the First Local Player's Viewport can project a world location to a screen
				* position.
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Whether the projection is possible or not.
				*/
				static bool CanSafeProjectWorldToScreen(const UObject* WorldContext);

				/**
				* Check whether the First Local Player's Viewport can de-project a screen position to a 
				* world location.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Whether the de-projection is possible or not.
				*/
				static bool CanDeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Safely check whether the First Local Player's Viewport can de-project a screen position to a
				* world location.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Log
				* return				Whether the de-projection is possible or not.
				*/
				static bool CanSafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely check whether the First Local Player's Viewport can de-project a screen position to a
				* world location.
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Whether the de-projection is possible or not.
				*/
				static bool CanSafeDeprojectScreenToWorld(const UObject* WorldContext);

				/**
				* Transforms the given 2D screen space coordinate into a 3D world-space point and direction.
				* 
				* @param Context			The calling context.
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param WorldPosition		(out) Corresponding 3D position in world space.
				* @param WorldDirection		(out) World space direction vector away from the camera at the given 2d point.
				* return					Whether the deproject was successful or not.
				*/
				static bool DeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection);

				/**
				* Safely transforms the given 2D screen space coordinate into a 3D world-space point and direction.
				*
				* @param Context			The calling context.
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param WorldPosition		(out) Corresponding 3D position in world space.
				* @param WorldDirection		(out) World space direction vector away from the camera at the given 2d point.
				* @param Log
				* return					Whether the deproject was successful or not.
				*/
				static bool SafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely transforms the given 2D screen space coordinate into a 3D world-space point and direction.
				*
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param WorldPosition		(out) Corresponding 3D position in world space.
				* @param WorldDirection		(out) World space direction vector away from the camera at the given 2d point.
				* return					Whether the deproject was successful or not.
				*/
				static bool SafeDeprojectScreenToWorld(const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection);

				/**
				* Get the Viewport associated with the First Local Player.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Viewport
				*/
				static FSceneViewport* GetViewportChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Safely get the Viewport associated with the First Local Player.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Log
				* return				Viewport
				*/
				static FSceneViewport* GetSafeViewport(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely get the Viewport associated with the First Local Player.
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Viewport
				*/
				static FSceneViewport* GetSafeViewport(const UObject* WorldContext);

				/**
				* Get the current Size (GetSizeXY()) of the Viewport associated with the First Local Player.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Size of the viewport.
				*/
				static FIntPoint GetSizeChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Safely get the current Size (GetSizeXY()) of the Viewport associated with the First Local Player.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param Log
				* return				Size of the viewport.
				*/
				static FIntPoint GetSafeSize(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely get the current Size (GetSizeXY()) of the Viewport associated with the First Local Player.
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Size of the viewport.
				*/
				static FIntPoint GetSafeSize(const UObject* WorldContext);

				/**
				* Get the intersection between the de-projection of the screen position to a world ray (location and direction)
				* with a world plane (location and normal).
				* 
				* @param Context			The calling context.
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param Plane				Location and normal in World Space.
				* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
				* return					Whether the intersection exists or not.
				*/
				static bool GetScreenWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection);

				/**
				* Safely get the intersection between the de-projection of the screen position to a world ray (location and direction)
				* with a world plane (location and normal).
				*
				* @param Context			The calling context.
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param Plane				Location and normal in World Space.
				* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
				* @param Log
				* return					Whether the intersection exists or not.
				*/
				static bool GetSafeScreenWorldIntersection(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely get the intersection between the de-projection of the screen position to a world ray (location and direction)
				* with a world plane (location and normal).
				*
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param Plane				Location and normal in World Space.
				* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
				* return					Whether the intersection exists or not.
				*/
				static bool GetSafeScreenWorldIntersection(const UObject* WorldContext, const FVector2D& ScreenPosition, const FPlane& Plane, FVector& OutIntersection);
			};
		}
	}
}