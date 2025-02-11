// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetCoordinatorGameEvent.generated.h"

class UCsCoordinator_GameEvent;

UINTERFACE(Blueprintable)
class CSINPUT_API UCsGetCoordinatorGameEvent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSINPUT_API ICsGetCoordinatorGameEvent
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsCoordinator_GameEvent* GetCoordinator_GameEvent() const = 0;

	virtual void SetCoordinator_GameEvent(UCsCoordinator_GameEvent* InCoordinator) = 0;
};