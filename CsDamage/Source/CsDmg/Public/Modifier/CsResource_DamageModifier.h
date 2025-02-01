// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Damage
#include "Modifier/CsDamageModifier.h"

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NResource
		{
			// ModifierType (NCsDamage::NModifier::IModifier)
			using ModifierType = NCsDamage::NModifier::IModifier;

			/**
			* Container for holding a reference to an object that implements the interface: ModifierType (NCsDamage::NModifier::IModifier).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSDMG_API FResource : public TCsResourceContainer<ModifierType> {};

			using ModifierResourceType = NCsDamage::NModifier::NResource::FResource;

			/**
			* A manager handling allocating and deallocating objects that implement the interface: ModifierType (NCsDamage::NModifier::IModifier) and
			* are wrapped in the container: NCsDamage::NModifier::NResource::FResource.
			*/
			struct CSDMG_API FManager : public NCsResource::NManager::NPointer::TFixed<ModifierType, ModifierResourceType, 0> {};
		}
	}
}