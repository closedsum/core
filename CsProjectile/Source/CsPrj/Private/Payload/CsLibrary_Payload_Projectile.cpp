// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsLibrary_Payload_Projectile.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectileImplSlice.h"

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NLibrary
		{
			bool FLibrary::CopyChecked(const FString& Context, const PayloadType* From, PayloadType* To)
			{
				bool Result = false;

				// PooledObject
				{
					using SliceType = NCsPooledObject::NPayload::FImplSlice;
					using PayloadInterfaceType = NCsPooledObject::NPayload::IPayload;

					Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
				}
				// Projectile
				{
					using SliceType = NCsProjectile::NPayload::NImplSlice::FImplSlice;
					using PayloadInterfaceType = NCsProjectile::NPayload::IPayload;

					Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
				}
				return Result;
			}
		}
	}
}