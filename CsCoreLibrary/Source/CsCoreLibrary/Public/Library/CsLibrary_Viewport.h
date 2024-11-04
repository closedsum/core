// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "CsMacro_Misc.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class FSceneViewport;
class UGameViewportClient;

namespace NCsViewport
{
	namespace NLocal
	{
		namespace NPlayer
		{
			class CSCORELIBRARY_API FLibrary final
			{
			private:

				CS_DECLARE_STATIC_LOG_LEVEL

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
				static bool CanSafeProjectWorldToScreen(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Safely check whether the First Local Player's Viewport can project a world location to a screen
				* position.
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* return				Whether the projection is possible or not.
				*/
				static bool CanSafeProjectWorldToScreen(const UObject* WorldContext);

				/** 
				* Transforms the given 3D world-space point into a its 2D screen space coordinate.
				* 
				* @param Context					The calling context.
				* @param WorldContext				Object that contains a reference to a World (GetWorld() is Valid).
				* @param WorldPosition				World position to project.
				* @param OutScreenPosition			(out) Corresponding 2D position in screen space
				* @param bPlayerViewportRelative	Should this be relative to the player viewport subregion (useful when using player attached widgets in split screen)
				* return							Whether the project was successful or not.
				*/
				static bool ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const FVector3f& WorldPosition, FVector2f& OutScreenPosition, bool bPlayerViewportRelative = false);

				/**
				* Transforms the given 3D world-space points into respective 2D screen space coordinates.
				*
				* @param Context					The calling context.
				* @param WorldContext				Object that contains a reference to a World (GetWorld() is Valid).
				* @param WorldPositions				Array of World positions to project.
				* @param OutScreenPositions			(out) Array of Corresponding 2D positions in screen space
				* return							Whether the project was successful or not.
				*/
				static bool ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const TArray<FVector3f>& WorldPositions, TArray<FVector2f>& OutScreenPositions);

				/**
				* Transforms the given 3D world-space points into respective 2D screen space coordinates for the first Count number of Indices.
				* NOTE: The use case for this function is meant for pre-allocated / fixed size arrays.
				*
				* @param Context					The calling context.
				* @param WorldContext				Object that contains a reference to a World (GetWorld() is Valid).
				* @param WorldPositions				Array of World positions to project.
				* @param Indices					Array of Indices for the World Positions to project.
				* @param Count						
				* @param OutScreenPositions			(out) Array of Corresponding 2D positions in screen space
				* return							Whether the project was successful or not.
				*/
				static bool ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const TArray<FVector3f>& WorldPositions, const TArray<int32>& Indices, const int32& Count, TArray<FVector2f>& OutScreenPositions);

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
				static bool CanSafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
				* @param OutWorldPosition	(out) Corresponding 3D position in world space.
				* @param OutWorldDirection	(out) World space direction vector away from the camera at the given 2d point.
				* return					Whether the deproject was successful or not.
				*/
				static bool DeprojectScreenToWorldChecked(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection);

				/**
				* Safely transforms the given 2D screen space coordinate into a 3D world-space point and direction.
				*
				* @param Context			The calling context.
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param OutWorldPosition	(out) Corresponding 3D position in world space.
				* @param OutWorldDirection	(out) World space direction vector away from the camera at the given 2d point.
				* @param Log
				* return					Whether the deproject was successful or not.
				*/
				static bool SafeDeprojectScreenToWorld(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Safely transforms the given 2D screen space coordinate into a 3D world-space point and direction.
				*
				* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition		2D screen space to deproject.
				* @param OutWorldPosition	(out) Corresponding 3D position in world space.
				* @param OutWorldDirection	(out) World space direction vector away from the camera at the given 2d point.
				* return					Whether the deproject was successful or not.
				*/
				static bool SafeDeprojectScreenToWorld(const UObject* WorldContext, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection);

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
				static FSceneViewport* GetSafeViewport(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
				static FIntPoint GetSafeSize(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
				static bool GetScreenWorldIntersectionChecked(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection);

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
				static bool GetSafeScreenWorldIntersection(const FString& Context, const UObject* WorldContext, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
				static bool GetSafeScreenWorldIntersection(const UObject* WorldContext, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection);
			};
		}
	}
}

using CsLocalPlayerViewportLibrary = NCsViewport::NLocal::NPlayer::FLibrary;

namespace NCsViewport
{
	namespace NGame
	{
		class CSCORELIBRARY_API FLibrary final
		{
		public:

			/**
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			*
			* return
			*/
			static UGameViewportClient* GetClientChecked(const FString& Context, const UObject* WorldContext);
		};
	}
}

using CsGameViewportLibrary = NCsViewport::NGame::FLibrary;