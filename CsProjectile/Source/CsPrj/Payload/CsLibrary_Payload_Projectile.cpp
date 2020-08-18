// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsLibrary_Payload_Projectile.h"

// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectileImplSlice.h"

void FCsLibrary_Payload_Projectile::CopyChecked(const FString& Context, ICsPayload_Projectile* From, ICsPayload_Projectile* To)
{
	// PooledObject
	CopySliceChecked<FCsPayload_PooledObjectImplSlice, ICsPayload_PooledObject>(Context, From, To);
	// Projectile
	CopySliceChecked<FCsPayload_ProjectileImplSlice, ICsPayload_Projectile>(Context, From, To);
}