// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsLibrary_Cache_PooledObject.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Pool
#include "Managers/Pool/CsPooledObject.h"

namespace NCsPooledObject
{
	namespace NCache
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPooledObject::NCache::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPooledObject::NCache::FLibrary, GetSafeIndex);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPooledObject::NCache::FLibrary, SafeIsAllocated);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPooledObject::NCache::FLibrary, SafeQueueDeallocate);
				}
			}
		}

		#define CacheType NCsPooledObject::NCache::ICache

		CacheType* FLibrary::GetChecked(const FString& Context, UObject* Object)
		{
			// Check Object is Valid
			CS_IS_PTR_NULL_CHECKED(Object)
			// Check Object implements the interface: ICsPooledObject;
			ICsPooledObject* Interface = Cast<ICsPooledObject>(Object);

			checkf(Interface, TEXT("%s: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName()));

			CacheType* Cache = Interface->GetCache();

			checkf(Cache, TEXT("%s: Object: %s does NOT have a reference to a Cache (NCsPooledObject::NCache::ICache)."), *Context, *(Object->GetName()));

			return Cache;
		}

		CacheType* FLibrary::GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check Object is Valid
			CS_IS_PTR_NULL_RET_NULL(Object)
			// Check Object implements the interface: ICsPooledObject;
			ICsPooledObject* Interface = Cast<ICsPooledObject>(Object);

			if (!Interface)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName())));
				return nullptr;
			}

			CacheType* Cache = Interface->GetCache();

			if (!Cache)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object: %s does NOT have a reference to a Cache (NCsPooledObject::NCache::ICache)."), *Context, *(Object->GetName())));
			}
			return Cache;
		}

		CacheType* FLibrary::GetSafe(UObject* Object)
		{
			using namespace NCsPooledObject::NCache::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, Object, nullptr);
		}

		const int32& FLibrary::GetIndexChecked(const FString& Context, UObject* Object)
		{
			return GetChecked(Context, Object)->GetIndex();
		}

		const int32& FLibrary::GetSafeIndex(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (CacheType* Cache = GetSafe(Context, Object, Log))
			{
				return Cache->GetIndex();
			}
			return NCsCached::Ref::IndexNone;
		}

		const int32& FLibrary::GetSafeIndex(UObject* Object)
		{
			using namespace NCsPooledObject::NCache::NLibrary::NCached;

			const FString& Context = Str::GetSafeIndex;

			return GetSafeIndex(Context, Object, nullptr);
		}

		const bool& FLibrary::IsAllocatedChecked(const FString& Context, UObject* Object)
		{
			return GetChecked(Context, Object)->IsAllocated();
		}

		const bool& FLibrary::SafeIsAllocated(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (CacheType* Cache = GetSafe(Context, Object, Log))
			{
				return Cache->IsAllocated();
			}
			return NCsCached::Ref::False;
		}

		const bool& FLibrary::SafeIsAllocated(UObject* Object)
		{
			using namespace NCsPooledObject::NCache::NLibrary::NCached;

			const FString& Context = Str::SafeIsAllocated;

			return SafeIsAllocated(Context, Object, nullptr);
		}

		void FLibrary::QueueDeallocateChecked(const FString& Context, UObject* Object)
		{
			CacheType* Cache = GetChecked(Context, Object);

			if (!Cache->IsAllocated())
				return;

			Cache->QueueDeallocate();
		}

		void FLibrary::SafeQueueDeallocate(const FString& Context, UObject* Object, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (CacheType* Cache = GetSafe(Context, Object, Log))
			{
				if (!Cache->IsAllocated())
					return;

				Cache->QueueDeallocate();
			}
		}

		void FLibrary::SafeQueueDeallocate(UObject* Object)
		{
			using namespace NCsPooledObject::NCache::NLibrary::NCached;

			const FString& Context = Str::SafeQueueDeallocate;

			return SafeQueueDeallocate(Context, Object, nullptr);
		}

		#undef CacheType
	}
}