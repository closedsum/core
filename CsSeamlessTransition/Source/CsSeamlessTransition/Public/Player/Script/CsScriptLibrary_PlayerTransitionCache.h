// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsScriptLibrary_PlayerTransitionCache.generated.h"

UCLASS()
class CSSEAMLESSTRANSITION_API UCsScriptLibrary_PlayerTransitionCache : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Input
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsSeamlessTransition|Library|Player", meta = (DisplayName = "Input: Add Event", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Info"))
	static bool Input_AddEvent(const FString& Context, const UObject* WorldContextObject, const FCsGameEventInfo& Info);

	UFUNCTION(BlueprintCallable, Category = "CsSeamlessTransition|Library|Player", meta = (DisplayName = "Input: Add Event (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Info"))
	static void Input_AddEventChecked(const FString& Context, const UObject* WorldContextObject, const FCsGameEventInfo& Info, bool& OutSuccess);

#pragma endregion Input
};