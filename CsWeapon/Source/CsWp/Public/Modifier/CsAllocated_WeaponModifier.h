// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Modifier/Types/CsTypes_WeaponModifier.h"

class UObject;

// ModifierResourceType (NCsWeapon::NModifier::NResource::FResource)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NModifier, NResource, FResource)
// ModifierType (NCsWeapon::NModifier::IModifier)
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
		private:

			using ModifierResourceType = NCsWeapon::NModifier::NResource::FResource;
			using ModifierType = NCsWeapon::NModifier::IModifier;

		public:

			/** The Root for UCsManager_Weapon. */
			TWeakObjectPtr<UObject> Root;

			/** Container holding a reference to Modifier (a Weapon Modifier). */
			ModifierResourceType* Container;

			/** Projectile Modifier */
			ModifierType* Modifier;

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

			FORCEINLINE ModifierType* Get() const { return Modifier; }

			void Copy(UObject* InRoot, const ModifierType* From);

			void Copy(const FAllocated&From);

			void Transfer(FAllocated& To);

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