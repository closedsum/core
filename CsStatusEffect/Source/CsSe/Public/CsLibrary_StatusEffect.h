// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Container
#include "Containers/CsLibrary_InterfaceMap.h"
// Data
#include "CsStatusEffect.h"

namespace NCsStatusEffect
{
#define StatusEffectType NCsStatusEffect::IStatusEffect

	/**
	* Library for interface: DataType (NCsStatusEffect::NData::IData)
	*/
	struct CSSE_API FLibrary : public NCsInterfaceMap::TLibrary<StatusEffectType>
	{
	};

#undef StatusEffectType
}