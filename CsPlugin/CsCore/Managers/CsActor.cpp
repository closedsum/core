// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsActor.h"
#include "CsCore.h"

ACsActor::ACsActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Warning_FellOutOfWorld	   = TEXT("ACsActor::FellOutOfWorld");
	Warning_OutsideWorldBounds = TEXT("ACsActor::OutsideWorldBounds");
}

void ACsActor::Tick(float DeltaSeconds)
{
#if WITH_EDITOR
	OnTick_ScriptEvent.Broadcast(this, DeltaSeconds);
#endif // #if WITH_EDITOR
}