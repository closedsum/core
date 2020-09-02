// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"

#pragma once

struct CSPRJ_API ICsProjectileCache : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsProjectileCache() {}
};