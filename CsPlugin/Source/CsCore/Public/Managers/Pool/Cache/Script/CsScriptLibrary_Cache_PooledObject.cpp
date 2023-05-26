// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/Script/CsScriptLibrary_Cache_PooledObject.h"
#include "CsCore.h"

// Library
#include "Managers/Pool/Cache/CsLibrary_Cache_PooledObject.h"

// Cached
#pragma region

namespace NCsScriptLibraryCachePooledObject
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Cache_PooledObject, GetIndex);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Cache_PooledObject, IsAllocated);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Cache_PooledObject, QueueDeallocate);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Cache_PooledObject::UCsScriptLibrary_Cache_PooledObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

int32 UCsScriptLibrary_Cache_PooledObject::GetIndex(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryCachePooledObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetIndex : Context;

	typedef NCsPooledObject::NCache::FLibrary PooledObjectCacheLibrary;

	return PooledObjectCacheLibrary::GetSafeIndex(Context, Object);
}

bool UCsScriptLibrary_Cache_PooledObject::IsAllocated(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryCachePooledObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsAllocated : Context;

	typedef NCsPooledObject::NCache::FLibrary PooledObjectCacheLibrary;

	return PooledObjectCacheLibrary::SafeIsAllocated(Context, Object);
}

void UCsScriptLibrary_Cache_PooledObject::QueueDeallocate(const FString& Context, UObject* Object)
{
	using namespace NCsScriptLibraryCachePooledObject::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::QueueDeallocate : Context;

	typedef NCsPooledObject::NCache::FLibrary PooledObjectCacheLibrary;

	PooledObjectCacheLibrary::SafeQueueDeallocate(Context, Object);
}