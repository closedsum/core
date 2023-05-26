// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Damage
#include "Modifier/CsDamageModifier.h"

namespace NCsDamage
{
	namespace NModifier
	{
		// NCsDamage::NModifier::IModifier

		/**
		* Container for holding a reference to an object that implements the interface: NCsDamage::NModifier::IModifier.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSDMG_API FResource : public TCsResourceContainer<IModifier> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NModifier::IModifier and
		* are wrapped in the container: NCsDamage::NModifer::FResource.
		*/
		struct CSDMG_API FManager : public NCsResource::NManager::NPointer::TFixed<IModifier, FResource, 0> {};
	}
}