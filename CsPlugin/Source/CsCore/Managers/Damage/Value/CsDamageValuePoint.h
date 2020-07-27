// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

/**
* 
*/
class CSCORE_API ICsDamageValuePoint : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual const float& GetValue() const = 0;
};