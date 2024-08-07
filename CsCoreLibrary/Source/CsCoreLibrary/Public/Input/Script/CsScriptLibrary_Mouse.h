// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Mouse.generated.h"

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_Mouse : public UObject
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
	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool IsShowingCursor(const FString& Context, const UObject* WorldContextObject);

	/**
	* Check if the mouse cursor is being shown. This checks bShowMouseCursor == true
	* for the First Local Player Controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	* return					Whether or not the cursor is being shown.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (DisplayName = "Is Showing Cursor (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool IsShowingCursorChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

	/**
	* Show the mouse cursor. This sets bShowMouseCursor = true for the
	* First Local Player Controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool ShowCursor(const FString& Context, const UObject* WorldContextObject);

	/**
	* Show the mouse cursor. This sets bShowMouseCursor = true for the
	* First Local Player Controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (DisplayName = "Show Cursor (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void ShowCursorChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

	/**
	* Hide the mouse cursor. This sets bShowMouseCursor = false for the
	* Fist Local Player Controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool HideCursor(const FString& Context, const UObject* WorldContextObject);

	/**
	* Hide the mouse cursor. This sets bShowMouseCursor = false for the
	* Fist Local Player Controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (DisplayName = "Hide Cursor (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void HideCursorChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

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
	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
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
	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,X,Y"))
	static bool SetPosition(const FString& Context, const UObject* WorldContextObject, const int32& X, const int32& Y);

	/**
	* Set the mouse position to the center of the viewport.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool SetCenterOfViewport(const FString& Context, const UObject* WorldContextObject);

	/**
	* Refresh the mouse position.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool RefreshPosition(const FString& Context, const UObject* WorldContextObject);

	/**
	* Refresh the mouse position.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess			(out)
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (DisplayName = "Refresh Position (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void RefreshPositionChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

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
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Input|Mouse", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Plane"))
	static bool GetWorldIntersection(const FString& Context, const UObject* WorldContextObject, const FPlane4f& Plane, FVector3f& OutIntersection);

#pragma endregion Trace
};