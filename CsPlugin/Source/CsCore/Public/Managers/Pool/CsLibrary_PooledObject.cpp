// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsLibrary_PooledObject.h"

// Pool
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Pool/Cache/CsCache_PooledObject.h"

namespace NCsPooledObject
{
	bool FLibrary::IsAllocated(const FString& Context, ICsPooledObject* Object)
	{
		checkf(Object, TEXT("%s: Object is NULL."), *Context);

		typedef NCsPooledObject::NCache::ICache CacheType;

		CacheType* Cache = Object->GetCache();

		checkf(Cache, TEXT("%s: Object's Cache is NULL."), *Context);

		return Cache->IsAllocated();		
	}

	bool FLibrary::IsAllocated(const FString& Context, UObject* Object)
	{
		checkf(Object, TEXT("%s: Object is NULL."), *Context);

		ICsPooledObject* PooledObject = Cast<ICsPooledObject>(Object);

		checkf(PooledObject, TEXT("%s: Object: %s with Class: %s does NOT implement the interface: ICsPooledObject."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName()));

		return IsAllocated(Context, PooledObject);
	}
}