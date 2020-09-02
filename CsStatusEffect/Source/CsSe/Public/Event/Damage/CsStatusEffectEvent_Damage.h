// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

struct ICsDamageEvent;

/**
*/
struct CSSE_API ICsStatusEffectEvent_Damage : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	/**
	*
	*
	* return
	*/
	virtual ICsDamageEvent* GetDamageEvent() const = 0;
};