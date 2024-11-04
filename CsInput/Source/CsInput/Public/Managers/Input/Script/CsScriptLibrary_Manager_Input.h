// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Types
#include "CsMacro_Log.h"
#include "Managers/Input/CsManager_Input_Delegates.h"
// Input
#include "Managers/Input/Action/CsInputActionMap.h"

#include "CsScriptLibrary_Manager_Input.generated.h"

class UCsManager_Input;

UCLASS()
class CSINPUT_API UCsScriptLibrary_Manager_Input : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	CS_DECLARE_STATIC_LOG_ERROR

// Get
#pragma region
public:

	/**
	* Get the Manager_Input associated with the player controller with ControllerId.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	* return				Manager_Input
	*/
	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,ControllerId"))
	static UObject* Get(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId);

	/**
	* Get the Manager_Input associated with the player controller with ControllerId.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	* @param OutSuccess		(out)
	* return				Manager_Input
	*/
	UFUNCTION(BlueprintPure, Category = "CsInput|Library|Manager|Input", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,ControllerId"))
	static UObject* GetChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess);

#pragma endregion Get

public:

	/**
	* Call Manager_Input->Init() on the PlayerController with ControllerId and
	* implements the interface: ICsGetManagerInput
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static bool Init(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId);

	/**
	* Call Manager_Input->Init() on all PlayerControllers that implement the interface: ICsGetManagerInput
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool InitAll(const FString& Context, const UObject* WorldContextObject);

// InputActionMap
#pragma region

	// Set
#pragma region
public:

	/**
	* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Map			A EnumStructFlag (contains a bit flag).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Map"))
	static bool SetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map);

	/**
	* Sets the bit (Map) in CurrentInputActionMap for player controller with ConrollerId.
	*		
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	* @param Map			A EnumStructFlag (contains a bit flag).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Map"))
	static bool SetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map);

#pragma endregion Set

	// Clear
#pragma region
public:

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Map			A EnumStructFlag (contains a bit flag).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Map"))
	static bool ClearFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the player controller with ControllerId.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	* @param Map			A bit flag. See FECsInputActionMap.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Map"))
	static bool ClearInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map);

#pragma endregion Clear

	// Reset
#pragma region
public:

	/**
	* Resets the CurrentInputActionMap to 0 for the first local player controller.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool ResetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject);

	/**
	* Resets the CurrentInputActionMap to 0 for local player controller with ControllerId.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static bool ResetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId);

	/**
	* Resets the CurrentInputActionMap to 0 for all local player controllers.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool ResetAllInputActionMap(const FString& Context, const UObject* WorldContextObject);

#pragma endregion Reset

#pragma endregion InputActionMap

// ICsManager_Input_Event
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Manager|Input", meta = (DisplayName = "BindToEvent: On AnyKey Pressed", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static void BindToEvent_OnAnyKey_Pressed(const FString& Context, UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsManagerInput_ScriptPassable_OnAnyKey_Pressed Delegate);

#pragma endregion ICsManager_Input_Event
};