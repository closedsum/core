// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class FSceneViewport;
class UGameViewportClient;

// NCsTrace::NRequest::FRequest
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NRequest, FRequest)
// NCsTrace::NResponse::FResponse
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsTrace, NResponse, FResponse)

namespace NCsViewport
{
	namespace NLocal
	{
		namespace NPlayer
		{
			class CSCORE_API FLibrary final
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
				* Transforms the given 3D world-space point into a its 2D screen space coordinate.
				* 
				* @param Context					The calling context.
				* @param WorldContext				Object that contains a reference to a World (GetWorld() is Valid).
				* @param WorldPosition				World position to project.
				* @param ScreenPosition				(out) Corresponding 2D position in screen space
				* @param bPlayerViewportRelative	Should this be relative to the player viewport subregion (useful when using player attached widgets in split screen)
				* return							Whether the project was successful or not.
				*/
				static bool ProjectWorldToScreenChecked(const FString& Context, const UObject* WorldContext, const FVector& WorldPosition, FVector2D& ScreenPosition, bool bPlayerViewportRelative = false);

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

			// Trace
			#pragma region
			public:

			#define ResponseType NCsTrace::NResponse::FResponse
			#define RequestType NCsTrace::NRequest::FRequest

				/**
				* Perform a trace with the given Request.
				*  Request->Start is replaced by:
				*   de-projection of ScreenPosition
				*  Request->End is replaced by:
				*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition	2D screen space to deproject.
				* @param Request
				* @param Distance		(optional) The distance to project outward from the Request->Start.
				* return				Response
				*/
				static ResponseType* TraceChecked(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, RequestType* Request, const float& Distance = 1000000.0f);

				/**
				* Safely perform a trace with the given Request.
				*  Request->Start is replaced by:
				*   de-projection of ScreenPosition
				*  Request->End is replaced by:
				*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition	2D screen space to deproject.
				* @param Request
				* @param Distance		(optional) The distance to project outward from the Request->Start.
				* @param Log			(optional)
				* return				Response
				*/
				static ResponseType* SafeTrace(const FString& Context, const UObject* WorldContext, const FVector2D& ScreenPosition, RequestType* Request, const float& Distance = 1000000.0f, void(*Log)(const FString&) = &FCsLog::Warning);

				/**
				* Safely perform a trace with the given Request.
				*  Request->Start is replaced by:
				*   de-projection of ScreenPosition
				*  Request->End is replaced by:
				*	The result of the Request->Start + Distance * World Direction (of the de-projectile of the current mouse position).
				*
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param ScreenPosition	2D screen space to deproject.
				* @param Request
				* @param Distance		(optional) The distance to project outward from the Request->Start.
				* return				Response
				*/
				static ResponseType* SafeTrace(const UObject* WorldContext, const FVector2D& ScreenPosition, RequestType* Request, const float& Distance = 1000000.0f);

			#undef ResponseType
			#undef RequestType

			#pragma endregion Trace
			};
		}
	}

	namespace NGame
	{
		class CSCORE_API FLibrary final
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