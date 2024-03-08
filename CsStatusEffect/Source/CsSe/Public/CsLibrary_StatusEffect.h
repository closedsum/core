// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Container
#include "Containers/CsLibrary_InterfaceMap.h"
// Data
#include "CsStatusEffect.h"

namespace NCsStatusEffect
{
#define StatusEffectType NCsStatusEffect::IStatusEffect

	/**
	* Library for interface: StatusEffectType (NCsStatusEffect::IStatusEffect)
	*/
	struct CSSE_API FLibrary : public NCsInterfaceMap::TLibrary<StatusEffectType>
	{
	};

#undef StatusEffectType
}