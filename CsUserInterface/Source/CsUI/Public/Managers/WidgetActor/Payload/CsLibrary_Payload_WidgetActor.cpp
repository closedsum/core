// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Payload/CsLibrary_Payload_WidgetActor.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"

bool FCsLibrary_Payload_WidgetActor::CopyChecked(const FString& Context, const ICsPayload_WidgetActor* From, ICsPayload_WidgetActor* To)
{
	bool Result = false;

	if (HasUniqueBasedSlices(Context, From))
	{
		checkf(HasUniqueBasedSlices(Context, To), TEXT("%s: To does NOT have Unique Based Slices like From."), *Context);
		// PooledObject
		Result |= CopySliceChecked<FCsPayload_PooledObjectImplSlice, ICsPayload_PooledObject>(Context, From, To);
	}
	return Result;
}