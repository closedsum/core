// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsPooledObject.h"
#include "CsCore.h"

UCsPooledObject::UCsPooledObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsPooledObject::OnCreatePool()
{
	OnCreatePool_Event.Broadcast();
#if WITH_EDITOR
	OnCreatePool_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
}

void UCsPooledObject::DeAllocate()
{
	DeAllocate_Event.Broadcast();
#if WITH_EDITOR
	DeAllocate_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
}