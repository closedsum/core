// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Projectile
#include "Modifier/CsProjectileModifier.h"

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NResource
		{
			// ModifierType (NCsProjectile::NModifier::IModifier)
			using ModifierType = NCsProjectile::NModifier::IModifier;

			/**
			* Container for holding a reference to an object that implements the interface: NCsProjectile::NModifier::IModifier.
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSPRJ_API FResource : public TCsResourceContainer<ModifierType> {};

			/**
			* A manager handling allocating and deallocating objects that implement the interface: NCsProjectile::NModifier::IModifier and
			* are wrapped in the container: NCsProjectile::NModifer::FResource.
			*/
			struct CSPRJ_API FManager : public NCsResource::NManager::NPointer::TFixed<ModifierType, FResource, 0> {};
		}
	}
}