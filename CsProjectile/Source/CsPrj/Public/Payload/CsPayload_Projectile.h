// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

/**
*/
struct CSPRJ_API ICsPayload_Projectile : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsPayload_Projectile(){}

	virtual const FVector& GetDirection() const = 0;

	virtual const FVector& GetLocation() const = 0;
};