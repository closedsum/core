// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsCoordinator_GameEvent_Delegates.generated.h"

USTRUCT()
struct CSINPUT_API FCsCoordinator_GameEvent_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsCoordinator_GameEvent_Delegates_STUB()
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsCoordinatorGameEvent_OnProcessGameEventInfo, const FECsGameEventCoordinatorGroup&, Group, const FCsGameEventInfo&, Info);

namespace NCsGameEvent
{
	namespace NCoordinator
	{
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProcessGameEventInfo, const FECsGameEventCoordinatorGroup& /*Group*/, const FCsGameEventInfo& /*Info*/);
	}
}