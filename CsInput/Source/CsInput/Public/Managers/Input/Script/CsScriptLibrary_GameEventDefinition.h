// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEventDefinition.h"

#include "CsScriptLibrary_GameEventDefinition.generated.h"

UCLASS()
class CSINPUT_API UCsScriptLibrary_GameEventDefinition : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Check whether a definition exists for Event.
	*
	* @param Context	The calling context.
	* @param Event		Game Event.
	* return			Whether the definition exists for Event.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Event"))
	static bool DoesExist(const FString& Context, const FECsGameEvent& Event);

	/**
	* Add
	*
	* @param Context			The calling context.
	* @param Definition			Game Event Definition.
	* return					Whether adding the definition was successfully added or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Definition"))
	static bool Add(const FString& Context, const FCsGameEventDefinition& Definition);

	/**
	* Add
	*
	* @param Context			The calling context.
	* @param Definition			Game Event Definition.
	* return					Whether adding the definition was successfully added or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Input", meta = (WorldContext = "WorldContextObject", DisplayName = "Add: Action - 1 Or Word, No Complete Value", AutoCreateRefTerm = "Context,Definition"))
	static bool Add_ActionOneOrWordNoCompletedValue(const FString& Context, const FCsGameEventDefinitionActionOneOrWordNoCompletedValue& Definition);

	/**
	* Remove
	*
	* @param Context	The calling context.
	* @param Event		Game Event.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsInput|Library|Input", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Event"))
	static void Remove(const FString& Context, const FECsGameEvent& Event);
};