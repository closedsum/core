// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsLog.h"
#pragma once

namespace NCsDamage
{
	namespace NEvent
	{
	#define EventType NCsDamage::NEvent::IEvent

		/**
		* Library for interface: (EventType) NCsDamage::NEvent::IEvent
		*/
		struct CSCORE_API FLibrary final : public TCsLibrary_InterfaceMap<EventType>
		{
		public:

			/**
			* Copy the values from From to To with checks.
			* Currently supports To types of:
			*  NCsDamage::NEvent::FImpl (NCsDamage::NEvent::IEvent)
			*
			* @param Context	The calling context.
			* @param From		What to copy.
			* @param To			What to copy to.
			* return			Whether the copy was performed successfully.
			*/
			static bool CopyChecked(const FString& Context, const EventType* From, EventType* To);

			/**
			* Set the damage on the Event with checks.
			*
			* @param Context	The calling context.
			* @param Event
			* return			Whether the damage was set successfully.
			*/
			static bool SetDamageChecked(const FString& Context, EventType* Event);

			static float GetSafeDamage(const FString& Context, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);
		};

	#undef EventType
	}
}