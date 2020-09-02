// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsStatusEffect_Damage;
struct ICsDamageRange;

/**
* Interface to describe modifying a damage range (ICsDamageRange) from 
*  a status effect (ICsData_StatusEffect_Damage).
*/
struct CSSE_API ICsStatusEffectModifier_DamageRange : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsStatusEffectModifier_DamageRange() {}

	/**
	* Modify the damage Range. This range is a copy of the DamageRange from Data,
	* which implements the interface ICsData_StatusEffect_Damage.
	*
	* @param Data	The data from which the Range was copied. This serves
	*				as a type and a way to check if and how the Range should be modified.
	* @param Range	The copy of the DamageRange from Data, which implements the interface:
					ICsData_StatusEffect_Damage, to be modified.
	*				NOTE: This range is allocated and must be freed at end of use.
	*/
	virtual void Modify(ICsData_StatusEffect_Damage* Data, ICsDamageRange* Range) = 0;
};