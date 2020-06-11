// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsProjectileWeapon.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsProjectileWeapon : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSWP_API ICsProjectileWeapon
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void Fire() = 0;
};