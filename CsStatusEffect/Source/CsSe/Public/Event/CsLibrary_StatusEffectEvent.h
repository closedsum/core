// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsStatusEffect
{
	namespace NEvent
	{
	#define EventType NCsStatusEffect::NEvent::IEvent

		/**
		* Library for interface: EventType (NCsStatusEffect::NEvent::IEvent)
		*/
		struct CSSE_API FLibrary final : public TCsLibrary_InterfaceMap<EventType>
		{
			/**
			* Copy the values from From to To with checks.
			* Currently supports To types of:
			*  NCsStatusEffect::NEvent::FImpl (NCsStatusEffect::NEvent::IEvent)
			*  NCsStatusEffect::NEvent::NDamage::FImpl (NCsStatusEffect::NEvent::NDamage::IDamage)
			*
			* @param Context	The calling context
			* @param From		What to copy.
			* @param To			What to copy to.
			* return			Whether the copy was performed successfully.
			*/
			static bool CopyChecked(const FString& Context, const EventType* From, EventType* To);
		};

	#undef EventType
	}
}