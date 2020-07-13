// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Damage/CsTypes_Damage.h"
#include "Engine/EngineTypes.h"
#pragma once

/**
*
*/
struct CSCORE_API ICsDamageExpression : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsDamageExpression() {}

	virtual float GetDamage() const = 0;

	virtual const FECsDamageType& GetType() const = 0;
};