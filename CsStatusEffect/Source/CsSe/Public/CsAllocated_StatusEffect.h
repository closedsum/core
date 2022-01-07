// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_StatusEffect.h"

class UObject;

// NCsStatusEffect::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsStatusEffect, FResource)
// NCsStatusEffect::IStatusEffect
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsStatusEffect, IStatusEffect)

namespace NCsStatusEffect
{
	/**
	* Container for an allocated object which implements the interface:
	* ModifierType (NCsStatusEffect::IStatusEffect). This container is used to some what cleanly free
	* the object after use.
	*/
	struct CSSE_API FAllocated final
	{
	private:

		typedef NCsStatusEffect::IStatusEffect StatusEffectType;

	public:

		/** The Root for UCsCoordinator_StatusEffect. */
		TWeakObjectPtr<UObject> Root;

		/** Container holding a reference to Status Effect. */
		FResource* Container;

		/** Status Effect */
		StatusEffectType* StatusEffect;

		/** The Type (or struct / class) of Modifier. This is used for 
			quicker deallocation from UCsCoordinator_StatusEffect. */
		FECsStatusEffect Type;

		FAllocated() :
			Root(nullptr),
			Container(nullptr),
			StatusEffect(nullptr),
			Type()
		{
		}

		~FAllocated();

		UObject* GetRoot() const;

		FORCEINLINE StatusEffectType* Get() const { return StatusEffect; }

		void CopyFrom(UObject* InRoot, const StatusEffectType* From);

		void Copy(const FAllocated& From);

		FORCEINLINE void Clear()
		{
			Root		 = nullptr;
			Container	 = nullptr;
			StatusEffect = nullptr;
			Type		 = EMCsStatusEffect::Get().GetMAX();
		}

		/**
		* Clear / null out all members and deallocate the Container.
		*/
		void Reset();
	};
}