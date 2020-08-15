// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

/**
* 
*/
struct CSCORE_API ICsDamageRange : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual const float& GetMinRange() const = 0;

	virtual const float& GetMaxRange() const = 0;
};