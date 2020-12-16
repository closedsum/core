// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Containers/CsLibrary_InterfaceMap.h"

#pragma once

namespace NCsPooledObject
{
	namespace NCache
	{
	#define CacheType NCsPooledObject::NCache::ICache

		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<CacheType>
		{
		};

	#undef CacheType
	}
}