// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Payload/CsLibrary_Payload_UserWidget.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"

bool FCsLibrary_Payload_UserWidget::CopyChecked(const FString& Context, const NCsUserWidget::NPayload::IPayload* From, NCsUserWidget::NPayload::IPayload* To)
{
	bool Result = false;

	if (HasUniqueBasedSlices(Context, From))
	{
		checkf(HasUniqueBasedSlices(Context, To), TEXT("%s: To does NOT have Unique Based Slices like From."), *Context);
		// PooledObject
		{
			typedef NCsPooledObject::NPayload::IPayload PayloadInterfaceType;
			typedef NCsPooledObject::NPayload::FImplSlice SliceType;

			Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
		}
	}
	return Result;
}