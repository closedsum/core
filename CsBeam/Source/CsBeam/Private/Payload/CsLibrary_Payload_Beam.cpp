// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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