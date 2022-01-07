// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// StatusEffect
#include "CsStatusEffect.h"

namespace NCsStatusEffect
{
#define StatusEffectType NCsStatusEffect::IStatusEffect

	/**
	* Container for holding a reference to an object that implements the interface: StatusEffectType (NCsStatusEffect::IStatusEffect).
	* This serves as an easy way for a Manager Resource to keep track of the resource.
	*/
	struct CSSE_API FResource : public TCsResourceContainer<StatusEffectType> {};

	/**
	* A manager handling allocating and deallocating objects that implement the interface: StatusEffectType (NCsStatusEffect::IStatusEffect) and
	* are wrapped in the container: NCsStatusEffect::FResource.
	*/
	struct CSSE_API FManager : public TCsManager_ResourcePointerType_Fixed<StatusEffectType, FResource, 0> {};

#undef StatusEffectType
}