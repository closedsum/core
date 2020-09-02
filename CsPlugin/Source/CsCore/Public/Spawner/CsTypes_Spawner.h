// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"

struct CSCORE_API ICsSpawnerParams : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsSpawnerParams() {}
};