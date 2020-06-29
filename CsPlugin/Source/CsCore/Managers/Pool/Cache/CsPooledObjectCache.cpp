// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsPooledObjectCache.h"

const FName ICsPooledObjectCache::Name = FName("ICsPooledObjectCache");

namespace NCsPooledObjectCache
{
	FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsPooledObjectCache* Cache)
	{
		FCsInterfaceMap* InterfaceMap = Cache->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("%s: Cache failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."), *Context);

		return InterfaceMap;
	}
}