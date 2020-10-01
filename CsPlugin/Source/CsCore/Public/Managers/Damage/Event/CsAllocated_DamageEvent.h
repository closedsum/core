// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;
struct FCsResource_DamageEvent;

namespace NCsDamage {
	namespace NEvent { 
		struct IEvent; } }

namespace NCsDamage
{
	namespace NEvent
	{
		/**
		* Container for an allocated object which implements the interface
		* NCsDamage::NEvent::IEvent. This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSCORE_API FAllocated
		{
		public:

			UObject* Root;

			FCsResource_DamageEvent* Container;

			IEvent* Event;

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Event(nullptr)
			{
			}

			FORCEINLINE const IEvent* GetEvent() const
			{
				return Event;
			}

			void Set(UObject* InRoot, FCsResource_DamageEvent* InContainer);

			void CopyFrom(UObject* InRoot, const IEvent* From);

			void CopyFrom(const FAllocated* Event);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}