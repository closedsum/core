// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Coordinators/GameplayTag/CsTypes_Coordinator_GameplayTag.h"

#include "CsCoordinator_GameplayTag_Delegates.generated.h"

USTRUCT()
struct CSGAMEPLAYTAGS_API FCsCoordinator_GameplayTag_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsCoordinator_GameplayTag_Delegates_STUB()
	{
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsCoordinatorGameplayTag_OnProcessGameplayTagEvent, const FECsGameplayTagCoordinatorGroup&, Group, const FCsGameplayTagEvent&, Event);
// NOTE: For scripts (i.e. Python) that don't handle const ref properly
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsCoordinatorGameplayTag_OnProcessGameplayTagEvent2, FECsGameplayTagCoordinatorGroup, Group, FCsGameplayTagEvent, Event);
	// Override
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsOverride_OnProcessGameplayTagEventImpl, const FECsGameplayTagCoordinatorGroup&, Group, const FCsGameplayTagEvent&, Event);
		// NOTE: For scripts (i.e. Python) that don't handle const ref properly
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsOverride_OnProcessGameplayTagEventImpl2, FECsGameplayTagCoordinatorGroup, Group, FCsGameplayTagEvent, Event);

namespace NCsGameplayTag
{
	namespace NCoordinator
	{
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProcessGameplayTagEvent, const FECsGameplayTagCoordinatorGroup& /*Group*/, const FCsGameplayTagEvent& /*Event*/);
	}
}