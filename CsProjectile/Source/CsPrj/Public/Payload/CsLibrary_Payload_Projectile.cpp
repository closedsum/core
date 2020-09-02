// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsLibrary_Payload_Projectile.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectileImplSlice.h"

bool FCsLibrary_Payload_Projectile::CopyChecked(const FString& Context, const ICsPayload_Projectile* From, ICsPayload_Projectile* To)
{
	bool Result = false;

	// PooledObject
	Result |= CopySliceChecked<FCsPayload_PooledObjectImplSlice, ICsPayload_PooledObject>(Context, From, To);
	// Projectile
	Result |= CopySliceChecked<FCsPayload_ProjectileImplSlice, ICsPayload_Projectile>(Context, From, To);

	return Result;
}