// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Runnable/Cache/CsCache_Runnable.h"

// Runnable
#include "Managers/Runnable/Payload/CsPayload_Runnable.h"

namespace NCsRunnable
{
	using PayloadType = NCsRunnable::NPayload::FImpl;

	void FCache::Allocate(PayloadType* Payload)
	{
		bAllocated = true;
		Owner = Payload->GetOwner();
		Time = Payload->Time;
		StackSize = Payload->StackSize;
		ThreadPriority = Payload->ThreadPriority;
	}
}