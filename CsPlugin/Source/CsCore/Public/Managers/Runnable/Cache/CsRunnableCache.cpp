// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Runnable/Cache/CsRunnableCache.h"

// Runnable
#include "Managers/Runnable/Payload/CsRunnablePayload.h"

void FCsRunnableCache::Allocate(FCsRunnablePayload* Payload)
{
	bAllocated = true;
	Owner = Payload->GetOwner();
	Time = Payload->Time;
	StackSize = Payload->StackSize;
	ThreadPriority = Payload->ThreadPriority;
}