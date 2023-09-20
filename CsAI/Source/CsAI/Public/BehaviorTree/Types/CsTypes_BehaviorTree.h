// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsTypes_BehaviorTree.generated.h"

UENUM(BlueprintType)
enum class ECsBlackboardNotificationResult : uint8
{
	RemoveObserver		UMETA(DisplayName = "RemoveObserver"),
	ContinueObserving	UMETA(DisplayName = "ContinueObserving")
};