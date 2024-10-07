// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsGameMode_SeamlessTransition.generated.h"

UINTERFACE(Blueprintable)
class CSSEAMLESSTRANSITION_API UCsGameMode_SeamlessTransition : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class AActor;

class CSSEAMLESSTRANSITION_API ICsGameMode_SeamlessTransition
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void QueueForSeamlessTravel(AActor* Actor) = 0;

	virtual void ClearQueueForSeamlessTravel() = 0;
};