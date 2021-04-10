// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Time/CsTypes_Time.h"

#include "CsScriptLibrary_Manager_Time.generated.h"

// Delegates
#pragma region

// Update
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCsScriptLibraryManagerTime_OnUpdate, const FECsUpdateGroup, Group, const FCsDeltaTime&, DeltaTime);

#pragma endregion Delegates


UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Time : public UObject
{
	GENERATED_UCLASS_BODY()

// Update
#pragma region
public:

	/**
	*
	*
	* @param WorldContextObject
	* @param Event / Delegate
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Time", meta = (DisplayName = "BindToEvent: OnUpdate", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnUpdate(const UObject* WorldContextObject, FCsScriptLibraryManagerTime_OnUpdate Delegate);
	//UPARAM(DisplayName = "Event") 
#pragma endregion Update
};