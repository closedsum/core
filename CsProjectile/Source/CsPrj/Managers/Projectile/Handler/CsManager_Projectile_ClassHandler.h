// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_ClassHandler.h"
// Types
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Managers/Projectile/CsProjectilePooled.h"
#pragma once

/**
*/
class CSPRJ_API FCsManager_Projectile_ClassHandler : public TCsManager_PooledObject_ClassHandler<FCsProjectilePooled, FCsProjectilePtr, FECsProjectileClass>
{
private:

	typedef TCsManager_PooledObject_ClassHandler<FCsProjectilePooled, FCsProjectilePtr, FECsProjectileClass> Super;

public:

	FCsManager_Projectile_ClassHandler();
};