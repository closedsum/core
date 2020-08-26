// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

struct ICsStatusEffectModifier;

/**
*/
struct CSSE_API ICsPayload_ProjectileModifierStatusEffect : virtual public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsPayload_ProjectileModifierStatusEffect(){}

	virtual const TArray<ICsStatusEffectModifier*>& GetStatusEffectModifiers() const = 0;
};