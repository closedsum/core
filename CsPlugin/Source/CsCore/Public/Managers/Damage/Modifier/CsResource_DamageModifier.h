// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Abstract_Fixed.h"
// Damage
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#pragma once

namespace NCsDamage
{
	namespace NModifier
	{
		// NCsDamage::NModifier::IModifier

		/**
		* Container for holding a reference to an object that implements the interface: NCsDamage::NModifier::IModifier.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSCORE_API FResource : public TCsResourceContainer<IModifier> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NModifier::IModifier and
		* are wrapped in the container: NCsDamage::NModifer::FResource.
		*/
		struct CSCORE_API FManager : public TCsManager_ResourceValueType_Abstract_Fixed<IModifier, FResource, 0> {};
	}
}