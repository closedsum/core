// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLastTickActor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsLastTickActor)

ACsLastTickActor::ACsLastTickActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_LastDemotable;
	PrimaryActorTick.EndTickGroup		   = TG_LastDemotable;

	bAllowTickBeforeBeginPlay = true;
}

void ACsLastTickActor::Tick(float DeltaSeconds)
{
	OnTick_Event.Broadcast(DeltaSeconds);
}