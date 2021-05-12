// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

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
				* Check whether the First Local Player's Viewport can de-project a screen position to a 
				* world location.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Whether the de-projection is possible or not.
				*/
				static bool CanDeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Transforms the given 2D screen space coordinate into a 3D world-space point and direction.
				* 
				* @param Context			The calling context.
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param WorldPosition		(out) Corresponding 3D position in world space.
				* @param WorldDirection		(out) World space direction vector away from the camera at the given 2d point.
				*/
				static bool DeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection);

				/**
				* Get the Viewport associated with the First Local Player.
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Viewport
				*/
				static FSceneViewport* GetViewportChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Get the current Size (GetSizeXY()) of the Viewport associated with the First Local Player.
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Size of the viewport.
				*/
				static FIntPoint GetSizeChecked(const FString& Context, const UObject* WorldContext);
			};
		}
	}
}