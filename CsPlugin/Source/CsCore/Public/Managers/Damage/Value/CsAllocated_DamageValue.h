// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
#pragma once

class UObject;

// NCsDamage::NValue::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, FResource)
// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)


namespace NCsDamage
{
	namespace NValue
	{
		/**
		* Container for an allocated object which implements the interface
		* ValueType (NCsDamage::NValue::IValue). This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSCORE_API FAllocated
		{
		public:

			/** The Root for UCsManager_Damage. */
			UObject* Root;

			/** Container holding a reference to Value (a Damage Value). */
			FResource* Container;

			/** Damage Value */
			IValue* Value;

			/** The Type (or struct / class) of Value. This is used for 
				quicker deallocation from UCsManager_Damage. */
			FECsDamageValue Type;

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Value(nullptr),
				Type()
			{
			}

			FORCEINLINE const IValue* GetValue() const { return Value; }

			void CopyFrom(UObject* InRoot, const IValue* From);

			void CopyFrom(const FAllocated* From);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}