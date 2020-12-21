// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#pragma once
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"

class UObject;

namespace NCsGameEvent
{
	namespace NCoordinator
	{
		struct CSCORE_API FLibrary
		{
			/**
			* Broadcast a GameEvent routed to the appropriated Group. Value and Location maybe be optional for 
			* certain GameEvents.
			* 
			* @param Context		The calling context.
			* @param ContextRoot	The root for Coordinator_GameEvent.
			* @param Group			The route / "group" to direct the GameEvent.
			* @param GameEvent		Game Event to broadcast.
			* @param Value			Value associated with the GameEvent.
			* @param Location		Location associated with the GameEvent.
			* @param Log			Log function for logging conditions that result in NOT processing
			*						the GameEvent.
			*/
			static void SafeBroadcastGameEvent(const FString& Context, UObject* ContextRoot, const FECsGameEventCoordinatorGroup& Group, const  FECsGameEvent& GameEvent, const float& Value, const FVector& Location, void(*Log)(const FString&) = nullptr);
		};
	}
}