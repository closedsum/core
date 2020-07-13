// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Engine/EngineTypes.h"
#pragma once

/**
*
*/
struct CSCORE_API ICsDamageShape : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsDamageShape() {}

	virtual const float& GetMinDamage() const = 0;

	virtual const float& GetMaxDamage() const = 0;

	virtual float CalculateDamage(const FVector& Origin, const FVector& Point) const = 0;
};