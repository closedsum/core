// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsLibrary_Payload_Projectile.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectileImplSlice.h"

bool FCsLibrary_Payload_Projectile::CopyChecked(const FString& Context, const NCsProjectile::NPayload::IPayload* From, NCsProjectile::NPayload::IPayload* To)
{
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