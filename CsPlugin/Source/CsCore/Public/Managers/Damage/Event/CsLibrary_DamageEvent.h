// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

// NCsDamage::NEvent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, FResource)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

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
			static bool SetDamageChecked(const FString&, EventType* Event);

		#define EventResourceType NCsDamage::NEvent::FResource
		#define DamageDataType NCsDamage::NData::IData

			/**
			* Create a resource container (EventResourceType (NCsDamage::NEvent::FResource)) from
			* a HitResult and Data which implements the interface: NCsDamage::NData::IData.
			* 
			* @param Context	The calling context.
			* @param HitResult
			* @param Data
			* return			Event resource.
			*/
			static const EventResourceType* CreateContainerChecked(const FString& Context, const FHitResult& HitResult, const DamageDataType* Data);

		#undef EventResourceType
		#undef DamageDataType
		};

	#undef EventType
	}
}