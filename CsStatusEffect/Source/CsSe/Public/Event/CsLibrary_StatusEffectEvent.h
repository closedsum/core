// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

/**
* Library for interface: NCsStatusEffect::NEvent::IEvent
*/
struct CSSE_API FCsLibrary_StatusEffectEvent : public TCsLibrary_InterfaceMap<NCsStatusEffect::NEvent::IEvent>
{
	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  NCsStatusEffect::NEvent::FImpl (NCsStatusEffect::NEvent::IEvent)
	*  NCsStatusEffect::NEvent::NDamage::FImpl (NCsStatusEffect::NEvent::NDamage::IDamage)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	* return			Whether the copy was performed successfully.
	*/
	static bool CopyChecked(const FString& Context, const NCsStatusEffect::NEvent::IEvent* From, NCsStatusEffect::NEvent::IEvent* To);
};