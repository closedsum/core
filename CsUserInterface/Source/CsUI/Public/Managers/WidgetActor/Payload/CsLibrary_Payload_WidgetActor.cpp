// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Payload/CsLibrary_Payload_WidgetActor.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"

bool FCsLibrary_Payload_WidgetActor::CopyChecked(const FString& Context, const NCsWidgetActor::NPayload::IPayload* From, NCsWidgetActor::NPayload::IPayload* To)
{
	bool Result = false;

	if (HasUniqueBasedSlices(Context, From))
	{
		checkf(HasUniqueBasedSlices(Context, To), TEXT("%s: To does NOT have Unique Based Slices like From."), *Context);
		// PooledObject
		{
			typedef NCsPooledObject::NPayload::FImplSlice SliceType;
			typedef NCsPooledObject::NPayload::IPayload PayloadInterfaceType;

			Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
		}
	}
	return Result;
}