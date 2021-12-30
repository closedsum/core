// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Modifier/CsTypes_ProjectileModifier.h"

class UObject;

// NCsProjectile::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FResource)
// NCsProjectile::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)


namespace NCsProjectile
{
	namespace NModifier
	{
		/**
		* Container for an allocated object which implements the interface
		* ModifierType (NCsProjectile::NModifier::IModifier). This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSPRJ_API FAllocated
		{
		public:

			/** The Root for UCsManager_Projectile. */
			TWeakObjectPtr<UObject> Root;

			/** Container holding a reference to Modifier (a Projectile Modifier). */
			FResource* Container;

			/** Projectile Modifier */
			IModifier* Modifier;

			/** The Type (or struct / class) of Modifier. This is used for 
				quicker deallocation from UCsManager_Projectile. */
			FECsProjectileModifier Type;

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
				Type	  = EMCsProjectileModifier::Get().GetMAX();
			}

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}