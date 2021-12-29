// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsLibrary_Payload_Beam.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Beam
#include "Payload/CsPayload_BeamImplSlice.h"

namespace NCsBeam
{
	namespace NPayload
	{
		#define PayloadType NCsBeam::NPayload::IPayload
		bool FLibrary::CopyChecked(const FString& Context, const PayloadType* From, PayloadType* To)
		{
		#undef PayloadType

			bool Result = false;

			// PooledObject
			{
				typedef NCsPooledObject::NPayload::FImplSlice SliceType;
				typedef NCsPooledObject::NPayload::IPayload PayloadInterfaceType;

				Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
			}
			// Beam
			{
				typedef NCsBeam::NPayload::FImplSlice SliceType;
				typedef NCsBeam::NPayload::IPayload PayloadInterfaceType;

				Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
			}

			return Result;
		}
	}
}