// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Handler/CsManager_PooledObject_DataHandler.h"
// Types
#include "Managers/Projectile/CsTypes_Projectile.h"
// Data
#include "Data/CsData_Projectile.h"
#include "Data/CsData_ProjectileInterfaceMap.h"
#pragma once

class CSPRJ_API FCsManager_Projectile_DataHandler : public TCsManager_PooledObject_DataHandler<ICsData_Projectile, FCsData_ProjectilePtr, FCsData_ProjectileInterfaceMap>
{
private:

	typedef TCsManager_PooledObject_DataHandler<ICsData_Projectile, FCsData_ProjectilePtr, FCsData_ProjectileInterfaceMap> Super;

public:

	FCsManager_Projectile_DataHandler();
};