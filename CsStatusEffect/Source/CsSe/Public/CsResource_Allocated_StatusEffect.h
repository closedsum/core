// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// StatusEffect
#include "CsAllocated_StatusEffect.h"

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)

namespace NCsStatusEffect
{
	namespace NAllocated
	{
	#define AllocatedType NCsStatusEffect::FAllocated

		/**
		* Container for holding a reference to an AllocatedType (NCsStatusEffect::FAllocated).
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSSE_API FResource : public TCsResourceContainer<AllocatedType> {};

		/**
		* A manager handling allocating and deallocating AllocatedTypes (NCsStatusEffect::FAllocated) and
		* are wrapped in the container: NCsStatusEffect::NAllocated::FResource.
		*/
		struct CSSE_API FManager : public NCsResource::NManager::NValue::TFixed<AllocatedType, FResource, 0> 
		{
		public:

		#define DataType NCsStatusEffect::NData::IData

			/**
			* Remove any Status Effects that share the same type from Data->GetStatusEffectsToRemove().
			* 
			* @param Data
			* return		Whether any Status Effects were removed.
			*/
			bool RemoveStatusEffects(const DataType* Data);

		#undef DataType
		};

	#undef AllocatedType
	}
}