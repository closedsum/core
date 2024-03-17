// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Macro/CsMacro_Namespace.h"

#include "CsWeapon_Event.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsWeapon_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsWeapon;

// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

class CSWP_API ICsWeapon_Event
{
	GENERATED_IINTERFACE_BODY()

public:

#define PooledPayloadType NCsPooledObject::NPayload::IPayload

// PooledObject
public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAllocate, const ICsWeapon* /*Weapon*/, PooledPayloadType* /*Payload*/);

	virtual FOnAllocate& GetOnAllocate_Event() = 0;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeallocate_Start, const ICsWeapon* /*Weapon*/);

	virtual FOnDeallocate_Start& GetOnDeallocate_Start_Event() = 0;

#undef PooledPayloadType
};