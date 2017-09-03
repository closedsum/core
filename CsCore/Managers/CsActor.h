// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Managers/CsPooledActor.h"
#include "CsActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsActorOnTick, ACsActor*, Actor, float, DeltaSeconds);

UCLASS()
class CSCORE_API ACsActor : public ACsPooledActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category = "0 Pool")
	FBindableEvent_CsActorOnTick OnTick_ScriptEvent;
};