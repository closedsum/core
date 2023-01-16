// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Spawner/Modifier/Types/CsTypes_SpawnerModifier.h"

class UObject;

// NCsSpawner::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, FResource)
// NCsSpawner::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, IModifier)

namespace NCsSpawner
{
	namespace NModifier
	{
		/**
		* Container for an allocated object which implements the interface
		* ModifierType (NCsSpawner::NModifier::IModifier). This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSCORE_API FAllocated
		{
		public:

		#define ModifierType NCsSpawner::NModifier::IModifier

			/** The Root for UCsManager_Weapon. */
			TWeakObjectPtr<UObject> Root;

			/** Container holding a reference to Modifier (a Spawner Modifier). */
			FResource* Container;

			/** Projectile Modifier */
			ModifierType* Modifier;

			/** The Type (or struct / class) of Modifier. This is used for 
				quicker deallocation from UCsManager_Weapon. */
			FECsSpawnerModifier Type;

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
				Type	  = EMCsSpawnerModifier::Get().GetMAX();
			}

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();

		#undef ModifierType
		};
	}
}