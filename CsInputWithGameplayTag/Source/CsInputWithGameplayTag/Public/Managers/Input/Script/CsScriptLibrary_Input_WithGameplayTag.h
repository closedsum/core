// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input_WithGameplayTag.h"

#include "CsScriptLibrary_Input_WithGameplayTag.generated.h"

UCLASS()
class CSINPUTWITHGAMEPLAYTAG_API UCsScriptLibrary_Input_WithGameplayTag : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "Event.Value: Get Bool", AutoCreateRefTerm = "Event"))
	static bool Event_Value_GetBool(const FCsInput_WithGameplayTag_Event& Event)
	{
		return Event.Value.Get<bool>();
	}

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "Event.Value: Get Float",AutoCreateRefTerm = "Event"))
	static float Event_Value_GetFloat(const FCsInput_WithGameplayTag_Event& Event)
	{
		return Event.Value.Get<float>();
	}

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "Event.Value: Get Vector2D", AutoCreateRefTerm = "Event"))
	static FVector2D Event_Value_GetVector2D(const FCsInput_WithGameplayTag_Event& Event)
	{
		return Event.Value.Get<FVector2D>();
	}

	UFUNCTION(BlueprintPure, Category = "CsEnhancedInputLibrary|Library|Input", meta = (DisplayName = "Event.Value: Get Vector", AutoCreateRefTerm = "Event"))
	static FVector Event_Value_GetVector(const FCsInput_WithGameplayTag_Event& Event)
	{
		return Event.Value.Get<FVector>();
	}
};