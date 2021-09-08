// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"

#pragma once

/**
*/
struct CSCORE_API ICsReset : public ICsGetInterfaceMap
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