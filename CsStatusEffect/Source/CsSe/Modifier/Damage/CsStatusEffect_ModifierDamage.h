// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

/**
* Interface to describe modifying a damage object (ICsDamageValue or ICsDamageRange)
*  from a status effect (ICsStatusEffect_Damage)
*/
class CSSE_API ICsStatusEffect_ModifierDamage : public ICsGetInterfaceMap
{
public:

	static const FName Name;
};