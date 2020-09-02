// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

/**
* Interface to describe modifying a status effect
*/
struct CSSE_API ICsStatusEffectModifier : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsStatusEffectModifier() {}
};