// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGameState_Transition.generated.h"

UINTERFACE(Blueprintable)
class CSSEAMLESSTRANSITION_API UCsGameState_Transition : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSEAMLESSTRANSITION_API ICsGameState_Transition
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual bool HasFinishedTransitionOut() const = 0;

	virtual void TransitionOut() = 0;
};