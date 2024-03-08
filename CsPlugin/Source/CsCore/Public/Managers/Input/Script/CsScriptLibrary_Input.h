// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "InputCoreTypes.h"
// Input
#include "GameFramework/PlayerInput.h"
#include "Managers/Input/Action/CsInputAction.h"

#include "UObject/Object.h"

#include "CsScriptLibrary_Input.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Input : public UObject
{
	GENERATED_UCLASS_BODY()

// Key
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Context,Device,Key"))
	static bool IsKeyValidForDevice(const FString& Context, const ECsInputDevice& Device, const FKey& Key);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Context,Mode,Key"))
	static bool IsKeyValidForMode(const FString& Context, const ECsInputMode& Mode, const FKey& Key);


	/**
	* Get the Keys for Device associated with Action.
	*
	* @param Context	The calling context.
	* @param Action
	* @param Device
	* @param OutKeys	(out)
	* @param Log		(optional)
	* return			Whether any keys for Device are associated with Action.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Context,Action,Device"))
	static bool GetKeysByDevice(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device, TArray<FKey>& OutKeys);

	/**
	* Get the Key for Device associated with Action.
	* NOTE: If there is MORE than ONE Key, return the FIRST Key.
	*
	* @param Context	The calling context
	* @param Action
	* @param Device
	* @param Log		(optional)
	* return			Key for Device associated with Action.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Context,Action,Device"))
	static FKey GetKey(const FString& Context, const FECsInputAction& Action, const ECsInputDevice& Device);

#pragma endregion Key

// Mapping
#pragma region
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

	/**
	* Replace a Mapping (FInputActionKeyMapping or FInputAxisKeyMapping) with name: Action.GetFName() and Key for
	* the PlayerInput associated with ControllerId.
	* NOTE: Assumes there is only ONE Key associated with the Device (i.e. there is only ONE Mouse, Keyboard, Gamepad, ... etc Key).
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Device
	* @param Action
	* @param Key
	* @param Scale				Only relevant if the Action is of type Axis.
	* return					Whether a mapping was successfully added.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Device,Action,Key,Scale"))
	static bool ReplaceActionMapping(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const ECsInputDevice& Device, const FECsInputAction& Action, const FKey& Key, const float& Scale = 0.0f);

#pragma endregion Mapping

// Action
#pragma region
public:

	/**
	* Check if the Action is associated with the Key.
	* This looks at InputSettings.
	*
	* @param Context	The calling context.
	* @param Action
	* @param Key
	* return			Whether the Action is associated with the Key or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Context,Action,Key"))
	static bool IsActionAssociatedWithKey(const FString& Context, const FECsInputAction& Action, const FKey& Key);

#pragma endregion Action

// Mode
#pragma region
public:

	/**
	* Check if the bit associated with Mode is set on the Mask.
	* 
	* @param Mask
	* @param Mode
	* return Whether the bit associated with Mode is set on Mask.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Input", meta = (AutoCreateRefTerm = "Mask,Mode"))
	static bool TestBitflag_InputMode(const int32& Mask, const ECsInputMode& Mode);

#pragma endregion Mode
};