// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsStartPlay_Event.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSCORE_API UCsStartPlay_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsStartPlay_Event_OnStartPlay, UObject*, Object);

class CSCORE_API ICsStartPlay_Event
{
	GENERATED_IINTERFACE_BODY()

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartPlay, UObject* /*Object*/);

	virtual FOnStartPlay& GetOnStartPlay_Event() = 0;
	virtual FCsStartPlay_Event_OnStartPlay& GetOnStartPlay_ScriptEvent() = 0;
};