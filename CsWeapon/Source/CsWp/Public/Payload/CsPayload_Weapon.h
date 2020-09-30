// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsWeapon
{
	namespace NPayload
	{
		struct CSWP_API IPayload : virtual public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload() {}
		};
	}
}