// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"

#pragma once

/**
*/
struct CSCORE_API ICsReset : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsReset(){}

	/**
	*
	*/
	virtual void Reset() = 0;
};