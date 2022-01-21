// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerWeapon.generated.h"

class UCsManager_Weapon;

UINTERFACE(Blueprintable)
class CSWP_API UCsGetManagerWeapon : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSWP_API ICsGetManagerWeapon
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Weapon* GetManager_Weapon() const = 0;

	virtual void SetManager_Weapon(UCsManager_Weapon* InManager) = 0;
};