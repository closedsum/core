// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/CsTypes_Input.h"

#include "CsScriptLibrary_GameEventDefinition.generated.h"

UCLASS()
class CSCORE_API UCsScriptLibrary_GameEventDefinition : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Add
	*
	* @param Context			The calling context.
	* @param Event				Game Event.
	* @param Definition			Game Event Definition.
	* return					Whether adding the definition was successfully added or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,Event,Definition"))
	static bool Add(const FString& Context, const FECsGameEvent& Event, const FCsGameEventDefinition& Definition);
};