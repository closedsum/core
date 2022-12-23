// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Weapon
#include "Spawner/Modifier/CsSpawnerModifier.h"

namespace NCsSpawner
{
	namespace NModifier
	{
		// ModifierType (NCsSpawner::NModifier::IModifier)

		/**
		* Container for holding a reference to an object that implements the interface: ModifierType (NCsSpawner::NModifier::IModifier).
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSCORE_API FResource : public TCsResourceContainer<IModifier> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: ModifierType (NCsSpawner::NModifier::IModifier)
		* and are wrapped in the container: ModifierType (NCsSpawner::NModifer::FResource).
		*/
		struct CSCORE_API FManager : public NCsResource::NManager::NPointer::TFixed<IModifier, FResource, 0> {};
	}
}