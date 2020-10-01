// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsDamageRange.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

/**
* Library for interface: ICsDamageRange
*/
struct CSCORE_API FCsLibrary_DamageRange : public TCsLibrary_InterfaceMap<NCsDamage::NRange::IRange>
{
	/**
	* Copy the values from From to To with checks.
	* Currently supports To types of:
	*  NCsDamage::NRange::FImpl (NCsDamage::NRange::IRange)
	*
	* @param Context	The calling context.
	* @param From		What to copy.
	* @param To			What to copy to.
	*/
	static bool CopyChecked(const FString& Context, const NCsDamage::NRange::IRange* From, NCsDamage::NRange::IRange* To);
};