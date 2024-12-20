// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Game/Transition/CsGameInstance_Transition_Delegates.h"

#include "CsGameInstance_Transition_Event.generated.h"

UINTERFACE(Blueprintable)
class CSSEAMLESSTRANSITION_API UCsGameInstance_Transition_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSEAMLESSTRANSITION_API ICsGameInstance_Transition_Event
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using OnStartTransitionOutEventType = NCsGameInstance::NTransition::FOut_OnStart;
		using OnFinishTransitionEventType = NCsGameInstance::NTransition::FOnFinish;
	};

public:

	virtual _::OnStartTransitionOutEventType& GetTransitionOut_OnStart_Event() = 0;
	virtual _::OnFinishTransitionEventType& GetTransition_OnFinish_Event() = 0;
};