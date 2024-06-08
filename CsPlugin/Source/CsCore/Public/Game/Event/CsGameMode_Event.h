// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Game/CsGameMode_Delegates.h"

#include "CsGameMode_Event.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsGameMode_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGameMode_Event
{
	GENERATED_IINTERFACE_BODY()

public:

#define OnPostSeamlessTravelCompleteEventType NCsGameMode::NSeamlessTravel::NPost::FOnComplete

	virtual FCsGameMode_PostSeamlessTravel_OnComplete& GetPostSeamlessTravel_OnComplete_ScriptEvent() = 0;

	virtual OnPostSeamlessTravelCompleteEventType& GetPostSeamlessTravel_OnComplete_Event() = 0;

#undef OnPostSeamlessTravelCompleteEventType
};