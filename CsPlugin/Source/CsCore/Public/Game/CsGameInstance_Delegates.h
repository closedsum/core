// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsGameInstance_Delegates.generated.h"

USTRUCT()
struct CSCORE_API FCsGameInstance_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsGameInstance_Delegates_STUB()
	{
	}
};

// Transition
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameInstance_Transition_OnFinish);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameInstance_TransitionOut_OnStart);
// TransitionAsDestination
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameInstance_TransitionAsDestination_OnStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameInstance_OnQueueExitGame);

namespace NCsGameInstance
{
	namespace NTransition
	{
		DECLARE_MULTICAST_DELEGATE(FOnFinish);
		DECLARE_MULTICAST_DELEGATE(FOut_OnStart);
	}

	namespace NTransitionAsDestination
	{
		DECLARE_MULTICAST_DELEGATE(FOnStart);
	}

	DECLARE_MULTICAST_DELEGATE(FOnQueueExitGame);
}