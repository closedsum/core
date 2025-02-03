// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsWeapon_Component.generated.h"

class ICsWeapon;

UINTERFACE(BlueprintType)
class CSWP_API UCsWeapon_Component: public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSWP_API ICsWeapon_Component
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void SetWeapon(ICsWeapon* InWeapon) = 0;
	virtual ICsWeapon* GetWeapon() const = 0;
};