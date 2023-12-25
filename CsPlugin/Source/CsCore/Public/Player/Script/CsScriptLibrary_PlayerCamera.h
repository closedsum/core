// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_PlayerCamera.generated.h"

class APlayerCameraManager;
class APawn;

UCLASS()
class CSCORE_API UCsScriptLibrary_PlayerCamera : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the PlayerCameraManager associated with PlayerController with ControllerId.
	*
	* @param Context			The calling context
	* @param WorldContextObject
	* @param ControllerId
	* return					PlayerCameraManager
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static APlayerCameraManager* Get(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId);

	/**
	* Get the PlayerCameraManager associated with PlayerController with ControllerId.
	*
	* @param Context			The calling context
	* @param WorldContextObject
	* @param ControllerId
	* @param OutSuccess			(out)
	* return					PlayerCameraManager
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static APlayerCameraManager* GetChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess);

	/**
	* Get the PlayerCameraManager associated with Pawn.
	*
	* @param Context			The calling context
	* @param Pawn
	* return					PlayerCameraManager
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (AutoCreateRefTerm = "Context"))
	static APlayerCameraManager* GetByPawn(const FString& Context, const APawn* Pawn);

	/**
	* Get the PlayerCameraManager associated with Pawn.
	*
	* @param Context			The calling context
	* @param Pawn
	* @param OutSuccess			(out)
	* return					PlayerCameraManager
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Get by Pawn (Checked)", AutoCreateRefTerm = "Context,ControllerId"))
	static APlayerCameraManager* GetByPawnChecked(const FString& Context, const APawn* Pawn, bool& OutSuccess);

#pragma endregion Get

// Orientation
#pragma region
public:

#pragma endregion Orientation
};