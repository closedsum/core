// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
		// NCsDamage::NValue::IValue

		/**
		* Container for holding a reference to an object that implements the interface: NCsDamage::NValue::IValue.
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSCORE_API FResource : public TCsResourceContainer<IValue> {};

		/**
		* A manager handling allocating and deallocating objects that implement the interface: NCsDamage::NValue::IValue and
		* are wrapped in the container: NCsDamage:;NValue::FResource.
		*/
		struct CSCORE_API FManager : public TCsManager_ResourcePointerType_Fixed<IValue, FResource, 0> {};
	}
}