// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

/**
*/
struct CSTYPES_API ICsReset : public ICsGetInterfaceMap
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