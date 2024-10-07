// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Game/SeamlessTransition/CsGameMode_SeamlessTransition_Delegates.h"

#include "CsGameMode_SeamlessTransition_Event.generated.h"

UINTERFACE(Blueprintable)
class CSSEAMLESSTRANSITION_API UCsGameMode_SeamlessTransition_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSEAMLESSTRANSITION_API ICsGameMode_SeamlessTransition_Event
{
	GENERATED_IINTERFACE_BODY()

private:

	typedef NCsGameMode::NSeamlessTravel::NPost::FOnComplete OnPostSeamlessTravelCompleteEventType;

public:

	virtual FCsGameMode_PostSeamlessTravel_OnComplete& GetPostSeamlessTravel_OnComplete_ScriptEvent() = 0;

	virtual OnPostSeamlessTravelCompleteEventType& GetPostSeamlessTravel_OnComplete_Event() = 0;
};