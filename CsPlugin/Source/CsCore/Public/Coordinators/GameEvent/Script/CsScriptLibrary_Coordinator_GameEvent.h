// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsScriptLibrary_Coordinator_GameEvent.generated.h"

class UCsCoordinator_GameEvent;

UCLASS()
class CSCORE_API UCsScriptLibrary_Coordinator_GameEvent : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get Coordinator_GameEvent.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* return				Coordinator_GameEvent
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Coordinator|GameEvent", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsCoordinator_GameEvent* Get(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get Coordinator_GameEvent.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess		(out)
	* return				Coordinator_GameEvent
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Coordinator|GameEvent", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsCoordinator_GameEvent* GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get

public:

	/**
	* Broadcast a GameEventInfo routed to the appropriated Group. Value and Location maybe be optional for
	* certain GameEvents.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group				The route / "group" to direct the GameEvent.
	* @param Info				Game Event Info to broadcast.
	* return					Whether the info was broadcasted or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Coordinator|GameEvent", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Group,Info"))
	static bool BroadcastGameEventInfo(const FString& Context, const UObject* WorldContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info);

	/**
	* Broadcast a GameEvent routed to the Group: GameInstance. Value and Location maybe be optional for
	* certain GameEvents.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event				Game Event to broadcast.
	* return					Whether the info was broadcasted or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Coordinator|GameEvent", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Event"))
	static bool BroadcastGameEvent_GameInstance(const FString& Context, const UObject* WorldContextObject, const FECsGameEvent& Event);
};