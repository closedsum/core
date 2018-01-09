// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "CsLastTickActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsLastTickActorOnTick, const float&);

UCLASS()
class CSCORE_API ACsLastTickActor : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	FBindableEvent_CsLastTickActorOnTick OnTick_Event;
};