// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "CsMacro_Namespace.h"

#include "CsScriptLibrary_GameStateImpl.generated.h"

// NCsGameState::NImpl::FLibrary
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsGameState, NImpl, FLibrary)

UCLASS()
class CSCORE_API UCsScriptLibrary_GameStateImpl : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	typedef NCsGameState::NImpl::FLibrary CsGameStateImplLibrary;

	static void(*LogError)(const FString&);

// ICsGameState_Startup
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Game State", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool IsStartupComplete(const FString& Context, const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Game State", meta = (DisplayName = "Is Startup Complete (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool IsStartupCompleteChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion ICsGameState_Startup

// ICsGameState_Transition
#pragma region
public:

	/**
	* Get whether the GameState has finished "Transitioning Out", which usually occurs when switching between levels.
	*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
	* 
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Game State", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool HasFinishedTransitionOut(const FString& Context, const UObject* WorldContextObject);

	/**
	* Begin the process of the GameState "Transitioning Out" (i.e. a Pre-Shutdown). THis is usually called before
	*  switching to another level.
	*  NOTE: Assumes GameState implements the interface: ICsGameState_Transition.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Game State", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool TransitionOut(const FString& Context, const UObject* WorldContextObject);

#pragma endregion ICsGameState_Transition
};