// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Game/Shutdown/CsGameInstance_Shutdown_Delegates.h"

#include "CsGameInstance_Shutdown_Event.generated.h"

UINTERFACE(Blueprintable)
class CSSEAMLESSTRANSITION_API UCsGameInstance_Shutdown_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSEAMLESSTRANSITION_API ICsGameInstance_Shutdown_Event
{
	GENERATED_IINTERFACE_BODY()

private:

	typedef NCsGameInstance::FOnPreShutdown OnPreShutdownEventType;
	typedef NCsGameInstance::FOnQueueExitGame OnQueueExitGameEventType;

public:

	virtual OnPreShutdownEventType& GetOnPreShutdown_Event();
	virtual FCsGameInstance_OnPreShutdown& GetOnPreShutdown_ScriptEvent();

	virtual OnQueueExitGameEventType& GetOnQueueExitGame_Event();
	virtual FCsGameInstance_OnQueueExitGame& GetOnQueueExitGame_ScriptEvent();
};