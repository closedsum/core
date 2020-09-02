// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

struct CSWP_API ICsWeaponPayload : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsWeaponPayload(){}
};