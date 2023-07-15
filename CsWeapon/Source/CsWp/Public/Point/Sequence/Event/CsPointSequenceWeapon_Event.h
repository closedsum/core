// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsPointSequenceWeapon_Event.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsPointSequenceWeapon_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsPointSequenceWeapon;

class CSWP_API ICsPointSequenceWeapon_Event
{
	GENERATED_IINTERFACE_BODY()

// Collision
public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHit, const ICsPointSequenceWeapon* /*Weapon*/, const FHitResult& /*Hit*/);

	virtual FOnHit& GetOnHit_Event() = 0;
};