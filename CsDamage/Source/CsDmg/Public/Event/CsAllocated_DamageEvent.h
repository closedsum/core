// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"
#include "CsMacro_Namespace.h"

class UObject;

// NCsDamage::NEvent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, FResource)
// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)

namespace NCsDamage
{
	namespace NEvent
	{
		/**
		* Container for an allocated object which implements the interface
		* NCsDamage::NEvent::IEvent. This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSDMG_API FAllocated
		{
		public:

			UObject* Root;

			FResource* Container;

			IEvent* Event;

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Event(nullptr)
			{
			}

			FORCEINLINE const IEvent* GetEvent() const { return Event; }

			void Set(UObject* InRoot, FResource* InContainer);

			void Copy(UObject* InRoot, const IEvent* From);

			void Copy(const FAllocated& From);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}