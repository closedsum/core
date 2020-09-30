// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"

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
				struct CSWP_API ITrace : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ITrace() {}
				};
			}
		}
	}
}