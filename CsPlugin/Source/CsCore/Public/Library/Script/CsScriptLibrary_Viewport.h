// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Viewport.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Viewport : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Transforms the given 2D screen space coordinate into a 3D world-space point and direction.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ScreenPosition		2D screen space to deproject.
	* @param WorldPosition		(out) Corresponding 3D position in world space.
	* @param WorldDirection		(out) World space direction vector away from the camera at the given 2d point.
	* return					Whether the deproject was successful or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Viewport", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ScreenPosition"))
	static bool DeprojectScreenToWorld(const FString& Context, const UObject* WorldContextObject, const FVector2f& ScreenPosition, FVector3f& OutWorldPosition, FVector3f& OutWorldDirection);

	/**
	* Safely get the current Size (GetSizeXY()) of the Viewport associated with the First Local Player.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return					Size of the viewport.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Viewport", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static FIntPoint GetSize(const FString& Context, const UObject* WorldContextObject);

	/**
	* Safely get the intersection between the de-projection of the screen position to a world ray (location and direction)
	* with a world plane (location and normal).
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ScreenPosition		2D screen space to deproject.
	* @param Plane				Location and normal in World Space.
	* @param OutIntersection	Intersection between ray from ScreenPosition and Plane.
	* @param Log
	* return					Whether the intersection exists or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Viewport", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ScreenPosition,Plane"))
	static bool GetScreenWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FVector2f& ScreenPosition, const FPlane4f& Plane, FVector3f& OutIntersection);
};