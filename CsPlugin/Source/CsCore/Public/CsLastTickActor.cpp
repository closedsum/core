// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "CsLastTickActor.h"
#include "CsCore.h"

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