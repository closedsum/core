// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

struct ICsDamageModifier;

/**
*/
struct CSPRJ_API ICsPayload_ProjectileModifierDamage : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsPayload_ProjectileModifierDamage(){}

	virtual const TArray<ICsDamageModifier*>& GetDamageModifiers() const = 0;
};