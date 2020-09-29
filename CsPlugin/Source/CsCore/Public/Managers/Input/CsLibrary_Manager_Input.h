// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Input/CsTypes_Input.h"

class UWorld;
class UCsManager_Input;

class CSCORE_API FCsLibrary_Manager_Input
{
public:

	static UCsManager_Input* GetFirstLocalManagerInput(UWorld* World);

	static UCsManager_Input* GetFirstLocalManagerInputChecked(const FString& Context, UWorld* World);

	static UCsManager_Input* GetFirstLocalManagerInputChecked(UWorld* World);

// InputActionMap
#pragma region

	// Set
#pragma region

	/**
	* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	static void SetFirstLocalCurrentInputActionMap(UWorld* World, const FECsInputActionMap& Map);
	
	/**
	* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param Context	The calling context.
	* @param World
	* @param Map		A EnumStructFlag (contains a bit flag).
	*/
	static void SetFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

	/**
	* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	static void SetFirstLocalCurrentInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map);
	
	/**
	* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A bit flag.
	*/
	static void SetFirstLocalCurrentInputActionMap(UWorld* World, const int32& Map);

	/**
	* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A bit flag.
	*/
	static void SetFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map);

	/**
	* Sets the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A bit flag.
	*/
	static void SetFirstLocalCurrentInputActionMapChecked(UWorld* World, const int32& Map);

#pragma endregion Set

	// Clear
#pragma region

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	static void ClearFirstLocalCurrentInputActionMap(UWorld* World, const FECsInputActionMap& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param Context	The calling context.
	* @param World
	* @param Map		A EnumStructFlag (contains a bit flag).
	*/
	static void ClearFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const FECsInputActionMap& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	static void ClearFirstLocalCurrentInputActionMapChecked(UWorld* World, const FECsInputActionMap& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A bit flag.
	*/
	static void ClearFirstLocalCurrentInputActionMap(UWorld* World, const int32& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param Context	The calling context.
	* @param World
	* @param Map		A EnumStructFlag (contains a bit flag).
	*/
	static void ClearFirstLocalCurrentInputActionMapChecked(const FString& Context, UWorld* World, const int32& Map);

	/**
	* Clears the bit (Map) in CurrentInputActionMap for the first local player controller.
	*
	* @param World
	* @param Map	A EnumStructFlag (contains a bit flag).
	*/
	static void ClearFirstLocalCurrentInputActionMapChecked(UWorld* World, const int32& Map);

#pragma endregion Clear

#pragma endregion InputActionMap
};