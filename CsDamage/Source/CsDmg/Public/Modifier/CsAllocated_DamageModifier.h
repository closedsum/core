// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Modifier/Types/CsTypes_DamageModifier.h"

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

			FORCEINLINE FResource* GetContainerChecked(const FString& Context) const
			{
				checkf(Container, TEXT("%s: Container is NULL."), *Context);
				return Container;
			}

			FORCEINLINE IModifier* GetChecked(const FString& Context) const
			{
				checkf(Modifier, TEXT("%s: Modifier is NULL."), *Context);
				return Modifier;
			}

			FORCEINLINE IModifier* Get() const { return Modifier; }

			void Copy(const UObject* WorldContext, const IModifier* From);

			void Copy(const FAllocated& From);

			void Transfer(FAllocated& To);

			FORCEINLINE void Clear()
			{
				Root = nullptr;
				Container = nullptr;
				Modifier = nullptr;
				Type = EMCsDamageModifier::Get().GetMAX();
			}

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}