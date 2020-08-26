// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

/**
* Interface to describe modifying a damage object (ICsDamageValue or ICsDamageRange)
*  from a damage expression (ICsData_Damage)
*/
struct CSCORE_API ICsDamageModifier : public ICsGetInterfaceMap
{
public:

	static const FName Name;
};