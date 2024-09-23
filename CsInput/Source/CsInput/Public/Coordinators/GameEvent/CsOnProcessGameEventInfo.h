// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsOnProcessGameEventInfo.generated.h"


UINTERFACE(Blueprintable)
class CSINPUT_API UCsOnProcessGameEventInfo : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSINPUT_API ICsOnProcessGameEventInfo
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void OnProcessGameEventInfo(const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info) = 0;
};