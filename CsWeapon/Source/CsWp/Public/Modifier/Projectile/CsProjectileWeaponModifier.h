// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsProjectileWeapon;

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NProjectile
		{
			struct CSWP_API IProjectile : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IProjectile() {}

				virtual void Modify(ICsProjectileWeapon* ProjectileWeapon) = 0;
			};
		}
	}
}