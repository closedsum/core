// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsPooledObjectCache.h"
#include "Containers/CsInterfaceMap.h"

#pragma once

struct CSCORE_API FCsLibrary_PooledObjectCache
{
	FORCEINLINE static FCsInterfaceMap* GetInterfaceMapChecked(const FString& Context, ICsPooledObjectCache* Cache)
	{
		return NCsInterfaceMap::GetInterfaceMapChecked<ICsPooledObjectCache>(Context, Cache);
	}

	template<typename T>
	FORCEINLINE static T* StaticCastChecked(const FString& Context, ICsPooledObjectCache* Cache)
	{
		return NCsInterfaceMap::StaticCastChecked<T, ICsPooledObjectCache>(Context, Cache);
	}
};