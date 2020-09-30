// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"

#pragma once

namespace NCsProjectile
{
	namespace NCache
	{
		struct CSPRJ_API ICache : virtual public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~ICache() {}
		};
	}
}