// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"

#pragma once

namespace NCsBeam
{
	namespace NCache
	{
		struct CSBEAM_API ICache : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~ICache() {}
		};
	}
}