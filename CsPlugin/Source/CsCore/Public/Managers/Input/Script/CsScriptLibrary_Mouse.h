// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Mouse.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Mouse : public UObject
{
	GENERATED_UCLASS_BODY()

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

	/**
	* Get the current mouse position in viewport space.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutPosition		(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void GetPosition(const FString& Context, const UObject* WorldContextObject, FIntPoint& OutPosition);

	/**
	* Set the mouse position in viewport space.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param X
	* @param Y
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,X,Y"))
	static void SetPosition(const FString& Context, const UObject* WorldContextObject, const int32& X, const int32& Y);

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
	static bool GetWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FPlane& Plane, FVector& OutIntersection);
};