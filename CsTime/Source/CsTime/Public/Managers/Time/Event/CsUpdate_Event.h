// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Managers/Time/CsTypes_Time.h"

#include "CsUpdate_Event.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSTIME_API UCsUpdate_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsUpdate_Event_OnUpdate, UObject*, Object, const FCsDeltaTime&, DeltaTime);

class CSTIME_API ICsUpdate_Event
{
	GENERATED_IINTERFACE_BODY()

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdate, const FCsDeltaTime& /*DeltaTime*/, UObject* /*Object*/);

	virtual FOnUpdate& GetOnUpdate_Event() = 0;
	virtual FCsUpdate_Event_OnUpdate& GetOnUpdate_ScriptEvent() = 0;
};