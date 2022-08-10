// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsTypes_Time.h"

#include "CsScriptLibrary_Manager_Time.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Time : public UObject
{
	GENERATED_UCLASS_BODY()

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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,WorldContextObject,Group"))
	static bool Pause(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group);

	/**
	* Unpause the update of Group.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* return					Whether the unpause was successfully executed or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,WorldContextObject,Group"))
	static bool Unpause(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group);

#pragma endregion Pause

public:

	/**
	*
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Time", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,WorldContextObject,Group"))
	static FCsDeltaTime GetTimeSinceStart(const FString& Context, const UObject* WorldContextObject, const FECsUpdateGroup& Group);
};