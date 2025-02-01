// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Cached.h"
#include "Modifier/Types/CsTypes_DamageModifier.h"

class UObject;

// ModifierResourceType (NCsDamage::NModifier::NResource::FResource)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NResource, FResource)
// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_2(NCsDamage, NModifier, Allocated)

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
		private:

			CS_USING_CACHED_FUNCTION_NAME_NESTED_2(NCsDamage, NModifier, Allocated);

			using ModifierResourceType = NCsDamage::NModifier::NResource::FResource;
			using ModifierType = NCsDamage::NModifier::IModifier;

		public:

			/** The Root for UCsManager_Damage. */
			TWeakObjectPtr<UObject> Root;

			/** Container holding a reference to Modifier (a Damage Modifier). */
			ModifierResourceType* Container;

			/** Damage Modifier */
			ModifierType* Modifier;

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

			FORCEINLINE ModifierResourceType* GetContainerChecked(const FString& Context) const
			{
				checkf(Container, TEXT("%s: Container is NULL."), *Context);
				return Container;
			}

			FORCEINLINE ModifierType* GetChecked(const FString& Context) const
			{
				checkf(Modifier, TEXT("%s: Modifier is NULL."), *Context);
				return Modifier;
			}

			FORCEINLINE IModifier* Get() const { return Modifier; }

			void Copy(const UObject* WorldContext, const ModifierType* From);

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