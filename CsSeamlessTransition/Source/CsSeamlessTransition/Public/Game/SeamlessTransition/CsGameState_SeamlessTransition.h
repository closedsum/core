// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsGameState_SeamlessTransition.generated.h"

UINTERFACE(Blueprintable)
class CSSEAMLESSTRANSITION_API UCsGameState_SeamlessTransition : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSEAMLESSTRANSITION_API ICsGameState_SeamlessTransition
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void SeamlessTransition_TransitionOut() = 0;

	virtual bool SeamlessTransition_Transition_IsTransitionOutComplete() const  = 0;

	virtual bool SeamlessTransition_Transition_IsStartupComplete() const = 0;
};