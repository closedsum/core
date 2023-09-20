// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsTypes_GameplayTask.generated.h"

UENUM(BlueprintType)
enum class ECsGameplayTaskState : uint8
{
	Uninitialized				UMETA(DisplayName = "Uninitialized"),
	AwaitingActivation			UMETA(DisplayName = "AwaitingActivation"),
	Paused						UMETA(DisplayName = "Paused"),
	Active						UMETA(DisplayName = "Active"),
	Finished					UMETA(DisplayName = "Finished"),
	ECsGameplayTaskState_MAX	UMETA(Hidden)
};