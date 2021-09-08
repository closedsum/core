// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsLog.h"

#pragma once

namespace NCsPooledObject
{
	namespace NCache
	{
	#define CacheType NCsPooledObject::NCache::ICache

		struct CSCORE_API FLibrary final : public TCsLibrary_InterfaceMap<CacheType>
		{
		public:

			/**
			* Get the Cache, which implements the interface: CacheType (NCsPooledObject::NCache::ICache),
			* from Object which implements the interface: ICsPooledObject.
			* 
			* @param Context	The calling context
			* @param Object		Implements the interface: ICsPooledObject.
			* return			Cache.
			*/
			static CacheType* GetChecked(const FString& Context, UObject* Object);

			/**
			* Safely get the Cache, which implements the interface: CacheType (NCsPooledObject::NCache::ICache),
			* from Object which implements the interface: ICsPooledObject.
			*
			* @param Context	The calling context
			* @param Object		Implements the interface: ICsPooledObject.
			* @param Log
			* return			Cache.
			*/
			static CacheType* GetSafe(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the Cache, which implements the interface: CacheType (NCsPooledObject::NCache::ICache),
			* from Object which implements the interface: ICsPooledObject.
			*
			* @param Context	The calling context
			* @param Object		Implements the interface: ICsPooledObject.
			* @param Log
			* return			Cache.
			*/
			static CacheType* GetSafe(UObject* Object);

			/**
			* Get the Index of the Object, which implements the interface: 
			* ICsPooledObject, in the pool it resides in.
			*
			* @param Context	The calling context.
			* @param Object		Implements the interface: ICsPooledObject.
			* return			Index
			*/
			static const int32& GetIndexChecked(const FString& Context, UObject* Object);

			/**
			* Safely get the Index of the Object, which implements the interface:
			* ICsPooledObject, in the pool it resides in.
			*
			* @param Context	The calling context.
			* @param Object		Implements the interface: ICsPooledObject.
			* @param Log
			* return			Index
			*/
			static const int32& GetSafeIndex(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the Index of the Object, which implements the interface:
			* ICsPooledObject, in the pool it resides in.
			*
			* @param Object		Implements the interface: ICsPooledObject.
			* return			Index
			*/
			static const int32& GetSafeIndex(UObject* Object);

			/**
			* Check whether the Object, which implements the interface:
			* ICsPooledObject, is allocated from the pool it resides in.
			*
			* @param Context	The calling context.
			* @param Object		Implements the interface: ICsPooledObject.
			* 
			* return			Whether the Object is allocated or not.
			*/
			static const bool& IsAllocatedChecked(const FString& Context, UObject* Object);

			/**
			* Safely check whether the Object, which implements the interface:
			* ICsPooledObject, is allocated from the pool it resides in.
			*
			* @param Context	The calling context.
			* @param Object		Implements the interface: ICsPooledObject.
			* @param Log
			*
			* return			Whether the Object is allocated or not.
			*/
			static const bool& SafeIsAllocated(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely check whether the Object, which implements the interface:
			* ICsPooledObject, is allocated from the pool it resides in.
			*
			* @param Object		Implements the interface: ICsPooledObject.
			*
			* return			Whether the Object is allocated or not.
			*/
			static const bool& SafeIsAllocated(UObject* Object);

			/**
			* Queue the Object, which implements the interface: ICsPooledObject,
			* for deallocation. This is the preferably way to deallocate a 
			* pooled object. Usually the Object will be deallocated the next frame.
			* 
			* @param Context	The calling context.
			* @param Object		Implements the interface: ICsPooledObject.
			*/
			static void QueueDeallocateChecked(const FString& Context, UObject* Object);

			/**
			* Safely queue the Object, which implements the interface: ICsPooledObject,
			* for deallocation. This is the preferably way to deallocate a
			* pooled object. Usually the Object will be deallocated the next frame.
			*
			* @param Context	The calling context.
			* @param Object		Implements the interface: ICsPooledObject.
			* @param Log
			*/
			static void SafeQueueDeallocate(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely queue the Object, which implements the interface: ICsPooledObject,
			* for deallocation. This is the preferably way to deallocate a
			* pooled object. Usually the Object will be deallocated the next frame.
			*
			* @param Object		Implements the interface: ICsPooledObject.
			*/
			static void SafeQueueDeallocate(UObject* Object);
		};

	#undef CacheType
	}
}