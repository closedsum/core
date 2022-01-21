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