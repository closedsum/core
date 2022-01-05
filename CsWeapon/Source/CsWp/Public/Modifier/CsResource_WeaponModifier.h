// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Weapon
#include "Modifier/CsWeaponModifier.h"

namespace NCsWeapon
{
	namespace NModifier
	{
		// NCsWeapon::NModifier::IModifier

		/**
		* Container for holding a reference to an object that implements the interface: NCsWeapon::NModifier::IModifier.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSWP_API FResource : public TCsResourceContainer<IModifier> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsWeapon::NModifier::IModifier and
		* are wrapped in the container: NCsWeapon::NModifer::FResource.
		*/
		struct CSWP_API FManager : public TCsManager_ResourcePointerType_Fixed<IModifier, FResource, 0> {};
	}
}