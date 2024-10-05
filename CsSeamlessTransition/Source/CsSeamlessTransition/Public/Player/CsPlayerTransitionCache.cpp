// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerTransitionCache.h"

// Library
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"
	// Common
#include "Library/CsLibrary_Valid.h"

namespace NCsPlayer
{
	namespace NTransition
	{
		namespace NInput
		{
			void FCache::Resolve(const FString& Context, const UObject* WorldContext)
			{
				const FECsGameEventCoordinatorGroup& Group = NCsGameEventCoordinatorGroup::ManagerInput0;

				for (const FCsGameEventInfo& Info : Events)
				{
					CS_IS_VALID_CHECKED(Info);

					CsGameEventCoordinatorLibrary::BroadcastGameEventChecked(Context, WorldContext, Group, Info);
				}

				Events.Reset(Events.Max());
			}
		}
	}
}