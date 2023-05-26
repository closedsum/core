// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"

class ICsWeapon;

namespace NCsWeapon
{
	namespace NOwner
	{
		namespace NEquip
		{
			namespace NParams
			{
				struct CSWP_API IParams : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					/**
					*/
					virtual ICsWeapon* GetWeapon() const = 0;
				};
			}
		}
	}
}