// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsGameInstance_Transition_Delegates.generated.h"

USTRUCT()
struct CSSEAMLESSTRANSITION_API FCsGameInstance_Transition_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsGameInstance_Transition_Delegates_STUB()
	{
	}
};

// Transition
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameInstance_Transition_OnFinish);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameInstance_TransitionOut_OnStart);

namespace NCsGameInstance
{
	namespace NTransition
	{
		DECLARE_MULTICAST_DELEGATE(FOnFinish);
		DECLARE_MULTICAST_DELEGATE(FOut_OnStart);
	}
}