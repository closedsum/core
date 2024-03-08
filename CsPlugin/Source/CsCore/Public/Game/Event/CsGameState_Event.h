// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Type
#include "Managers/Time/CsTypes_Time.h"

#include "CsGameState_Event.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsGameState_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// StartPlay
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameState_Event_OnStartPlay);
// Startup
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameState_Event_OnStartupComplete);
// Update
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsGameState_Event_OnUpdate, const FCsDeltaTime&, DeltaTime);
// Shutdown
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameState_Event_OnShutdown_Start);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsGameState_Event_OnShutdown);

class CSCORE_API ICsGameState_Event
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FCsGameState_Event_OnStartPlay& GetOnStartPlay_ScriptEvent() = 0;

	virtual FCsGameState_Event_OnStartupComplete& GetOnStartupComplete_ScriptEvent() = 0;

	virtual FCsGameState_Event_OnUpdate& GetOnUpdate_ScriptEvent() = 0;

	virtual FCsGameState_Event_OnShutdown_Start& GetOnShutdown_Start_ScriptEvent() = 0;

	virtual FCsGameState_Event_OnShutdown& GetOnShutdown_ScriptEvent() = 0;
};