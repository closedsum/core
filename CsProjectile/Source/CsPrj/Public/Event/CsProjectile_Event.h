// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Types/CsTypes_Macro.h"

#include "CsProjectile_Event.generated.h"

UINTERFACE(Blueprintable)
class CSPRJ_API UCsProjectile_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsProjectile;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

class CSPRJ_API ICsProjectile_Event
{
	GENERATED_IINTERFACE_BODY()

public:

#define PooledPayloadType NCsPooledObject::NPayload::IPayload

// PooledObject
public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAllocate, const ICsProjectile* /*Projectile*/, PooledPayloadType* /*Payload*/);

	virtual FOnAllocate& GetOnAllocate_Event() = 0;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeallocate_Start, const ICsProjectile* /*Projectile*/);

	virtual FOnDeallocate_Start& GetOnDeallocate_Start_Event() = 0;

#undef PooledPayloadType

// Collision
public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHit, const ICsProjectile* /*Projectile*/, const FHitResult& /*Hit*/);

	virtual FOnHit& GetOnHit_Event() = 0;
};