// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsOnProcessGameEventInfo.generated.h"


UINTERFACE(Blueprintable)
class CSCORE_API UCsOnProcessGameEventInfo : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSCORE_API ICsOnProcessGameEventInfo
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void OnProcessGameEventInfo(const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info) = 0;
};