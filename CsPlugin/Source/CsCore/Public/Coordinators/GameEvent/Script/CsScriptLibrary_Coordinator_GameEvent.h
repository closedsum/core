// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UObject/Object.h"
// Types
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsScriptLibrary_Coordinator_GameEvent.generated.h"
#pragma once

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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Coordinator|GameEvent", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static UCsCoordinator_GameEvent* Get(const FString& Context, const UObject* WorldContextObject);

#pragma endregion Get

public:

	/**
	* Broadcast a GameEvent routed to the appropriated Group. Value and Location maybe be optional for
	* certain GameEvents.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group				The route / "group" to direct the GameEvent.
	* @param Info				Game Event Info to broadcast.
	* return					Whether the info was broadcasted or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Coordinator|GameEvent", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Group,Info"))
	static bool BroadcastGameEvent(const FString& Context, const UObject* WorldContextObject, const FECsGameEventCoordinatorGroup& Group, const  FCsGameEventInfo& Info);

};