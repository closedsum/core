// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/CsPooledObjectOld.h"
#include "CsCore.h"

UCsPooledObjectOld::UCsPooledObjectOld(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsPooledObjectOld::OnCreatePool()
{
	OnCreatePool_Event.Broadcast();
#if WITH_EDITOR
	OnCreatePool_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
}

void UCsPooledObjectOld::DeAllocate()
{
	DeAllocate_Event.Broadcast();
#if WITH_EDITOR
	DeAllocate_ScriptEvent.Broadcast();
#endif // #if WITH_EDITOR
}