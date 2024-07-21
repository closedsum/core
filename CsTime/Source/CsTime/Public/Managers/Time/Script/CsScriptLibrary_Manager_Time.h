// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsTypes_Time.h"

#include "CsScriptLibrary_Manager_Time.generated.h"

class UCsManager_Time;

UCLASS()
class CSTIME_API UCsScriptLibrary_Manager_Time : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the reference to UCsManager_Time from WorldContextObject.
	*
	* @param Context		The calling context.
	* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	*						or
	*						A reference to the GameInstance.
	* return				UCsManager_Time.
	*/
	UFUNCTION(BlueprintPure, Category = "CsTime|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Time* Get(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get the reference to UCsManager_Time from WorldContextObject.
	*
	* @param Context		The calling context.
	* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	*						or
	*						A reference to the GameInstance.
	* @param OutSuccess		(out)
	* return				UCsManager_Time.
	*/
	UFUNCTION(BlueprintPure, Category = "CsTime|Library|Manager|Time", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsManager_Time* GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get

// Pause
#pragma region
public:

	/**
	* Pause the update of Group.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* return					Whether the pause was successfully executed or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsTime|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Group"))
	static bool Pause(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group);

	/**
	* Unpause the update of Group.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* return					Whether the unpause was successfully executed or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsTime|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Group"))
	static bool Unpause(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group);

#pragma endregion Pause

// Time
#pragma region
public:

	/**
	* Get the Current Time for Group (this takes into account Paused Time).
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsTime|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Group"))
	static FCsTime GetTime(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group);

	/**
	*
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsTime|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Group"))
	static FCsDeltaTime GetTimeSinceStart(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group);

	/**
	*
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* @param Scale
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsTime|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Group,Scale"))
	static bool SetScaledDeltaTime(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group, const float& Scale);

	/**
	*
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsTime|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Group"))
	static bool ResetScaledDeltaTime(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group);

#pragma endregion Time
};