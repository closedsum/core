// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsWeapon.generated.h"

UINTERFACE(Blueprintable)
class CSWP_API UCsWeapon : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_Weapon;

class CSWP_API ICsWeapon
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual ICsData_Weapon* GetData() const = 0;
};