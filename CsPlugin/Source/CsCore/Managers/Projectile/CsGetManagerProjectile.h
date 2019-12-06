// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerProjectile.generated.h"

class UCsManager_Projectile;

UINTERFACE(Blueprintable)
class UCsGetManagerProjectile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerProjectile
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Projectile* GetManager_Projectile() = 0;

	virtual void SetManager_Projectile(UCsManager_Projectile* InManager) = 0;
};