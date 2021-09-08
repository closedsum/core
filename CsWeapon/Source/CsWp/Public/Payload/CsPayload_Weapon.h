// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsWeapon
{
	namespace NPayload
	{
		struct CSWP_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload() {}
		};
	}
}