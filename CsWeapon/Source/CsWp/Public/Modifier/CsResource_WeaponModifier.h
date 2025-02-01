// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Weapon
#include "Modifier/CsWeaponModifier.h"

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NResource
		{
			// ModifierType (NCsWeapon::NModifier::IModifier)
			using ModifierType = NCsWeapon::NModifier::IModifier;

			/**
			* Container for holding a reference to an object that implements the interface: ModiferyType (NCsWeapon::NModifier::IModifier).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSWP_API FResource : public TCsResourceContainer<ModifierType> {};

			/**
			* A manager handling allocating and deallocating objects that implement the interface: ModiferyType (NCsWeapon::NModifier::IModifier) and
			* are wrapped in the container: NCsWeapon::NModifer::FResource.
			*/
			struct CSWP_API FManager : public NCsResource::NManager::NPointer::TFixed<ModifierType, FResource, 0> {};
		}
	}
}