// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Modifier/CsTypes_WeaponModifier.h"

class UObject;

// NCsWeapon::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, FResource)
// NCsWeapon::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)


namespace NCsWeapon
{
	namespace NModifier
	{
		/**
		* Container for an allocated object which implements the interface
		* ModifierType (NCsWeapon::NModifier::IModifier). This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSWP_API FAllocated
		{
		public:

			/** The Root for UCsManager_Weapon. */
			TWeakObjectPtr<UObject> Root;

			/** Container holding a reference to Modifier (a Weapon Modifier). */
			FResource* Container;

			/** Projectile Modifier */
			IModifier* Modifier;

			/** The Type (or struct / class) of Modifier. This is used for 
				quicker deallocation from UCsManager_Weapon. */
			FECsWeaponModifier Type;

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

			FORCEINLINE void Clear()
			{
				Root	  = nullptr;
				Container = nullptr;
				Modifier  = nullptr;
				Type	  = EMCsWeaponModifier::Get().GetMAX();
			}

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}