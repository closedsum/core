// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Pool/CsLibrary_PooledObject.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Pool
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Pool/Cache/CsCache_PooledObject.h"

namespace NCsPooledObject
{
	bool FLibrary::IsAllocated(const FString& Context, ICsPooledObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

		typedef NCsPooledObject::NCache::ICache CacheType;

		CacheType* Cache = Object->GetCache();

		checkf(Cache, TEXT("%s: Object's Cache is NULL."), *Context);

		return Cache->IsAllocated();		
	}

	bool FLibrary::IsAllocated(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

		ICsPooledObject* PooledObject = Cast<ICsPooledObject>(Object);

		checkf(PooledObject, TEXT("%s: Object: %s with Class: %s does NOT implement the interface: ICsPooledObject."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName()));

		return IsAllocated(Context, PooledObject);
	}
}