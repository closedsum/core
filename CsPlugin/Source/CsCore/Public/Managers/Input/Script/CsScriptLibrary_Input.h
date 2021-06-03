// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Input
#include "GameFrameWork/PlayerInput.h"

#include "UObject/Object.h"

#include "CsScriptLibrary_Input.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Input : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Add a specific KeyMapping (action mapping) for player with ControllerId.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId		Id for the player.
	* @param KeyMapping			Action Mapping.
	* return					Whether the KeyMapping was successfully added or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,KeyMapping"))
	static bool AddActionMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FInputActionKeyMapping& KeyMapping);

	/**
	* Add a specific KeyMapping (axis mapping) for player with ControllerId.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId		Id for the player.
	* @param KeyMapping			Action Mapping.
	* return					Whether the KeyMapping was successfully added or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,KeyMapping"))
	static bool AddAxisMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FInputAxisKeyMapping& KeyMapping);
};