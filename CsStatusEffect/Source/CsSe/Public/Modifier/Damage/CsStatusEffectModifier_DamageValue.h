// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsData_StatusEffect_Damage;
struct ICsDamageValue;

/**
* Interface to describe modifying a damage value (ICsDamageValue) from 
*  a status effect (ICsData_DamageStatus_Damage).
*/
struct CSSE_API ICsStatusEffectModifier_DamageValue : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsStatusEffectModifier_DamageValue() {}

	/**
	* Modify the damage Value. This value is a copy of the DamageValue from Data,
	* which implements the interface ICsData_StatusEffect_Damage.
	*
	* @param Data	The Data from which the Value was copied. This serves
	*				as a type and a way to check if and how the Value should be modified.
	* @param Value	The copy of the DamageValue from Data, which implements the interface:
					ICsData_StatusEffect_Damage, to be modified.
	*				NOTE: This value is allocated and must be freed at end of use.
	*/
	virtual void Modify(ICsData_StatusEffect_Damage* StatusEffect, ICsDamageValue* Value) = 0;
};