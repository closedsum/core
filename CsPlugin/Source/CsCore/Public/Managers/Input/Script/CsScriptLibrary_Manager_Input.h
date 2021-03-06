// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input.h"

#include "CsScriptLibrary_Manager_Input.generated.h"


UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Input : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Call Manager_Input->Init()
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static bool Init(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId);

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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Map"))
	static void SetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map);

	/**
	* Sets the bit (Map) in CurrentInputActionMap for player controller with ConrollerId.
	*		
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	* @param Map			A EnumStructFlag (contains a bit flag).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Map"))
	static void SetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map);

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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Map"))
	static void ClearFirstInputActionMap(const FString& Context, const UObject* WorldContextObject, const FECsInputActionMap& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the player controller with ControllerId.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	* @param Map			A bit flag. See FECsInputActionMap.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Map"))
	static void ClearInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const FECsInputActionMap& Map);

#pragma endregion Clear

	// Reset
#pragma region
public:

	/**
	* Resets the CurrentInputActionMap to 0 for the first local player controller.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void ResetFirstInputActionMap(const FString& Context, const UObject* WorldContextObject);

	/**
	* Resets the CurrentInputActionMap to 0 for all local player controllers.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static void ResetInputActionMap(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId);

#pragma endregion Reset

#pragma endregion InputActionMap
};