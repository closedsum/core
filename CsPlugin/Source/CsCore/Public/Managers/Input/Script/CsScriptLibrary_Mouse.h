// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Trace/CsTraceRequest.h"
#include "Managers/Trace/CsTraceResponse.h"

#include "CsScriptLibrary_Mouse.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Mouse : public UObject
{
	GENERATED_UCLASS_BODY()

// Show / Hide
#pragma region
public:

	/**
	* Check if the mouse cursor is being shown. This checks bShowMouseCursor == true
	* for the First Local Player Controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return					Whether or not the cursor is being shown.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool IsShowingCursor(const FString& Context, const UObject* WorldContextObject);

	/**
	* Show the mouse cursor. This sets bShowMouseCursor = true for the
	* First Local Player Controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void ShowCursor(const FString& Context, const UObject* WorldContextObject);

	/**
	* Hide the mouse cursor. This sets bShowMouseCursor = false for the
	* Fist Local Player Controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void HideCursor(const FString& Context, const UObject* WorldContextObject);

#pragma endregion Show / Hide

// Get / Set
#pragma region
public:

	/**
	* Get the current mouse position in viewport space.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutPosition		(out)
	* return					Whether current mouse position was obtained successfully.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetPosition(const FString& Context, const UObject* WorldContextObject, FIntPoint& OutPosition);

	/**
	* Set the mouse position in viewport space.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param X
	* @param Y
	* return					Whether current mouse position was set successfully.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,X,Y"))
	static bool SetPosition(const FString& Context, const UObject* WorldContextObject, const int32& X, const int32& Y);

	/**
	* Set the mouse position to the center of the viewport.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool SetCenterOfViewport(const FString& Context, const UObject* WorldContextObject);

#pragma endregion Get / Set

// Trace
#pragma region
public:

	/**
	* Get the intersection between the de-projection of the current mouse position (viewport space) to a world ray (location and direction)
	* with a world plane (location and normal).
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Plane				Location and normal in World Space.
	* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
	* return					Whether the intersection exists or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Plane"))
	static bool GetWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FPlane4f& Plane, FVector3f& OutIntersection);

	/**
	* Perform a trace with the given Request.
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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Request,Distance"))
	static bool Trace(const FString& Context, const UObject* WorldContextObject, const FCsTraceRequest& Request, const float& Distance, FCsTraceResponse& OutResponse);

#pragma endregion Trace
};