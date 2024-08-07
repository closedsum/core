// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Pool/Cache/Script/CsScriptLibrary_Cache_PooledObject.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Pool/Cache/CsLibrary_Cache_PooledObject.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Cache_PooledObject)

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