// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

/**
* Interface to describe modifying a damage object (ICsDamageValue or ICsDamageRange)
*  from a status effect (ICsData_StatusEffect_Damage)
*/
struct CSSE_API ICsStatusEffectModifier_Damage : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsStatusEffectModifier_Damage() {}
};