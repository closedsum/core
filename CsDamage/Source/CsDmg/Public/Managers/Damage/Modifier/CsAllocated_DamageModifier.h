// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Damage/Modifier/Types/CsTypes_DamageModifier.h"

class UObject;

// NCsDamage::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FResource)
// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)


namespace NCsDamage
{
	namespace NModifier
	{
		/**
		* Container for an allocated object which implements the interface
		* ValueType (NCsDamage::NModifier::IModifier). This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSDMG_API FAllocated
		{
		public:

			/** The Root for UCsManager_Damage. */
			TWeakObjectPtr<UObject> Root;

			/** Container holding a reference to Modifier (a Damage Modifier). */
			FResource* Container;

			/** Damage Modifier */
			IModifier* Modifier;

			/** The Type (or struct / class) of Modifier. This is used for 
				quicker deallocation from UCsManager_Damage. */
			FECsDamageModifier Type;

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Modifier(nullptr),
				Type()
			{
			}

			~FAllocated();

			UObject* GetRoot() const;

			FORCEINLINE const IModifier* GetModifier() const { return Modifier; }

			void CopyFrom(UObject* InRoot, const IModifier* From);

			void CopyFrom(const FAllocated* From);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}