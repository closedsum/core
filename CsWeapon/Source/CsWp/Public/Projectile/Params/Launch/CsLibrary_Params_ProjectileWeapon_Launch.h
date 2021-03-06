// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"

// Containers
#include "Containers/CsLibrary_InterfaceMap.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				struct CSWP_API FLibrary : public TCsLibrary_InterfaceMap<ILaunch>
				{
				};
			}
		}
	}
}