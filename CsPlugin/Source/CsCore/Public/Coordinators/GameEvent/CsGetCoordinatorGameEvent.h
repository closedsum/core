// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetCoordinatorGameEvent.generated.h"

class UCsCoordinator_GameEvent;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetCoordinatorGameEvent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSCORE_API ICsGetCoordinatorGameEvent
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsCoordinator_GameEvent* GetCoordinator_GameEvent() const = 0;

	virtual void SetCoordinator_GameEvent(UCsCoordinator_GameEvent* InCoordinator) = 0;
};