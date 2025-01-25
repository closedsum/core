// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Cached.h"

class UObject;

// ResourceType (NCsDamage::NEvent::FResource)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, FResource)
// EventType (NCsDamage::NEvent::IEvent)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_2(NCsDamage, NEvent, Allocated)

namespace NCsDamage
{
	namespace NEvent
	{
		/**
		* Container for an allocated object which implements the interface
		* EventType (NCsDamage::NEvent::IEvent). This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSDMG_API FAllocated
		{
		private:

			CS_USING_CACHED_FUNCTION_NAME_NESTED_2(NCsDamage, NEvent, Allocated);

			using ResourceType = NCsDamage::NEvent::FResource;
			using EventType =  NCsDamage::NEvent::IEvent;

		public:

			UObject* Root;

			ResourceType* Container;

			EventType* Event;

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Event(nullptr)
			{
			}

			FORCEINLINE const EventType* GetEvent() const { return Event; }

			void Set(UObject* InRoot, ResourceType* InContainer);

			void Copy(UObject* InRoot, const EventType* From);

			void Copy(const FAllocated& From);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}