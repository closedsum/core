// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

class ICsDamageEvent;

/**
*/
struct CSSE_API ICsStatusEffectDamageEvent : virtual public ICsGetInterfaceMap
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