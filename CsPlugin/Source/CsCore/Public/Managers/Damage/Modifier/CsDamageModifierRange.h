// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsData_Damage;
struct ICsDamageRange;

/**
* Interface to describe modifying a damage range (ICsDamageRange) from 
*  a damage data (ICsData_Damage).
*/
struct CSCORE_API ICsDamageModifierRange : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	/**
	* Modify the damage Range. This range is a copy of the DamageRange from Data.
	*
	* @param Data		The data from which the Range was copied. This serves
	*					as a type and a way to check if and how the Range should be modified.
	* @param Range		The copy of the DamageRange from Data to be modified.
	*					NOTE: This range is allocated and must be freed at end of use.
	*/
	virtual void Modify(ICsData_Damage* Data, ICsDamageRange* Range) = 0;
};