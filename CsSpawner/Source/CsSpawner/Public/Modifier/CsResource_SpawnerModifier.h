// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Weapon
#include "Modifier/CsSpawnerModifier.h"

namespace NCsSpawner
{
	namespace NModifier
	{
		// ModifierType (NCsSpawner::NModifier::IModifier)

		/**
		* Container for holding a reference to an object that implements the interface: ModifierType (NCsSpawner::NModifier::IModifier).
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSSPAWNER_API FResource : public TCsResourceContainer<IModifier> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: ModifierType (NCsSpawner::NModifier::IModifier)
		* and are wrapped in the container: ModifierType (NCsSpawner::NModifer::FResource).
		*/
		struct CSSPAWNER_API FManager : public NCsResource::NManager::NPointer::TFixed<IModifier, FResource, 0> {};
	}
}