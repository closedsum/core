// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsGameInstance_Shutdown_Delegates.generated.h"

USTRUCT()
struct CSSEAMLESSTRANSITION_API FCsGameInstance_Shutdown_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsGameInstance_Shutdown_Delegates_STUB()
	{
	}
};

// Shutdown
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameInstance_OnPreShutdown);
// Exit
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameInstance_OnQueueExitGame);

namespace NCsGameInstance
{
	DECLARE_MULTICAST_DELEGATE(FOnPreShutdown);
	DECLARE_MULTICAST_DELEGATE(FOnQueueExitGame);
}