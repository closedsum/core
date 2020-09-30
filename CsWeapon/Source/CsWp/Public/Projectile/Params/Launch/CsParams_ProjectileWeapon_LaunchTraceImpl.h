// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTrace.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				/**
				*/
				struct CSWP_API FTraceImpl : public ILaunch,
											 public ITrace
				{
				public:

					static const FName Name;

					FTraceImpl();

					~FTraceImpl();

				// ILaunch

				// Trace
				};
			}
		}
	}
}