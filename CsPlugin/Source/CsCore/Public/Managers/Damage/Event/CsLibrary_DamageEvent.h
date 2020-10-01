// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEvent.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

/**
* Library for interface: NCsDamage::NEvent::IEvent
*/
struct CSCORE_API FCsLibrary_DamageEvent : public TCsLibrary_InterfaceMap<NCsDamage::NEvent::IEvent>
{
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
	static bool CopyChecked(const FString& Context, const NCsDamage::NEvent::IEvent* From, NCsDamage::NEvent::IEvent* To);

	/**
	* Set the damage on the Event with checks.
	*
	* @param Context	The calling context.
	* @param Event
	* return			Whether the damage was set successfully.
	*/
	static bool SetDamageChecked(const FString&, NCsDamage::NEvent::IEvent* Event);
};