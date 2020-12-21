// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"
#include "CsCore.h"

// Coordinators
#include "Coordinators/GameEvent/CsCoordinator_GameEvent.h"

namespace NCsGameEvent
{
	namespace NCoordinator
	{
		void FLibrary::SafeBroadcastGameEvent(const FString& Context, UObject* ContextRoot, const FECsGameEventCoordinatorGroup& Group, const FECsGameEvent& GameEvent, const float& Value, const FVector& Location, void(*Log)(const FString&) /*= nullptr*/)
		{
			// Check ContextRoot is Valid.
			if (!ContextRoot)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: ContextRoot is NULL."), *Context));
				return;
			}
			// Check Group is Valid.
			if (!EMCsGameEventCoordinatorGroup::Get().IsValidEnum(Group))
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Group: %s is NOT Valid."), *Context, Group.ToChar()));
				return;
			}
			// Check GameEvent is Valid.
			if (!EMCsGameEvent::Get().IsValidEnum(GameEvent))
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: GameEvent: %s is NOT Valid."), *Context, GameEvent.ToChar()));
				return;
			}

			FCsGameEventInfo Info;
			Info.Event	  = GameEvent;
			Info.Value	  = Value;
			Info.Location = Location;

			// If Group == None, Process Immediately
			if (Group == NCsGameEventCoordinatorGroup::None)
			{
				UCsCoordinator_GameEvent::Get(ContextRoot)->ProcessGameEventInfo(Group, Info);
			}
			else
			{
				UCsCoordinator_GameEvent::Get(ContextRoot)->QueueGameEventInfo(Group, Info);
			}
		}
	}
}