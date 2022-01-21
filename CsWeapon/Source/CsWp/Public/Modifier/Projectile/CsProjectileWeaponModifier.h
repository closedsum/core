// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsProjectileWeapon;

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NModifier
		{
			struct CSWP_API IModifier : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IModifier() {}

				virtual void Modify(ICsProjectileWeapon* ProjectileWeapon) = 0;
			};
		}
	}
}