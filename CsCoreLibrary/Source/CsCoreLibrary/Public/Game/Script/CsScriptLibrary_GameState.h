// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_GameState.generated.h"

class AGameStateBase;

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_GameState : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get GameState from WorldContext.
	* 
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* return				GameState
	*/
	UFUNCTION(BlueprintPure, Category = "CsCoreLibrary|Library|Game State", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static AGameStateBase* Get(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get GameState from WorldContext.
	* 
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess		(out)
	* return				GameState
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|Library|Game State", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static AGameStateBase* GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get
};