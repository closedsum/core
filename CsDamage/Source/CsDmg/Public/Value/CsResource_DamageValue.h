// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Damage
#include "Value/CsDamageValue.h"

namespace NCsDamage
{
	namespace NValue
	{
		// NCsDamage::NValue::IValue

		/**
		* Container for holding a reference to an object that implements the interface: NCsDamage::NValue::IValue.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSDMG_API FResource : public TCsResourceContainer<IValue> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NValue::IValue and
		* are wrapped in the container: NCsDamage:;NValue::FResource.
		*/
		struct CSDMG_API FManager : public NCsResource::NManager::NPointer::TFixed<IValue, FResource, 0> {};
	}
}