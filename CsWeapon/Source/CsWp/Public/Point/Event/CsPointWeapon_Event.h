// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "CsMacro_Misc.h"
#include "Engine/HitResult.h"

#include "CsPointWeapon_Event.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsPointWeapon_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsPointWeapon;

class CSWP_API ICsPointWeapon_Event
{
	GENERATED_IINTERFACE_BODY()

// Collision
public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHit, const ICsPointWeapon* /*Weapon*/, const FHitResult& /*Hit*/);

	virtual FOnHit& GetOnHit_Event() = 0;
};