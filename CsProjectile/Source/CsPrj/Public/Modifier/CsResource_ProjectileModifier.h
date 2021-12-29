// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Projectile
#include "Modifier/CsProjectileModifier.h"

namespace NCsProjectile
{
	namespace NModifier
	{
		// NCsDamage::NModifier::IModifier

		/**
		* Container for holding a reference to an object that implements the interface: NCsProjectile::NModifier::IModifier.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSPRJ_API FResource : public TCsResourceContainer<IModifier> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsProjectile::NModifier::IModifier and
		* are wrapped in the container: NCsProjectile::NModifer::FResource.
		*/
		struct CSPRJ_API FManager : public TCsManager_ResourcePointerType_Fixed<IModifier, FResource, 0> {};
	}
}