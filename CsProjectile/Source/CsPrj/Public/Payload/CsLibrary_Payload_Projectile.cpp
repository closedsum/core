// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsLibrary_Payload_Projectile.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectileImplSlice.h"

namespace NCsProjectile
{
	namespace NPayload
	{
		#define PayloadType NCsProjectile::NPayload::IPayload
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
			// Projectile
			{
				typedef NCsProjectile::NPayload::FImplSlice SliceType;
				typedef NCsProjectile::NPayload::IPayload PayloadInterfaceType;

				Result |= CopySliceChecked<SliceType, PayloadInterfaceType>(Context, From, To);
			}

			return Result;
		}
	}
}