// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsStatusEffect_Damage;
struct ICsDamageValue;

/**
* Interface to describe modifying a damage value (ICsDamageValue) from 
*  a status effect (ICsDamageStatus_Damage).
*/
class CSSE_API ICsStatusEffect_ModifierDamageValue : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	/**
	* Modify the damage Value. This value is a copy of the DamageValue from StatusEffect.
	*
	* @param StatusEffect	The status effect from which the Value was copied. This serves
	*						as a type and a way to check if and how the Value should be modified.
	* @param Value			The copy of the DamageValue from StatusEffect to be modified.
	*						NOTE: This value is allocated and must be freed at end of use.
	*/
	virtual void Modify(ICsStatusEffect_Damage* StatusEffect, ICsDamageValue* Value) = 0;
};