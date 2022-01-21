// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Damage/Value/Types/CsTypes_DamageValue.h"

class UObject;

// NCsDamage::NValue::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, FResource)
// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsDamage
{
	namespace NValue
	{
		/**
		* Container for an allocated object which implements the interface
		* ValueType (NCsDamage::NValue::IValue). This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSDMG_API FAllocated
		{
		private:

			/** The Root for UCsManager_Damage. */
			TWeakObjectPtr<UObject> Root;

			/** Container holding a reference to Value (a Damage Value). */
			FResource* Container;

			/** Damage Value */
			IValue* Value;

			/** The Type (or struct / class) of Value. This is used for 
				quicker deallocation from UCsManager_Damage. */
			FECsDamageValue Type;

		public:

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Value(nullptr),
				Type()
			{
			}

			~FAllocated();

			UObject* GetRoot() const;
			FORCEINLINE const FResource* GetContainer() const { return Container; }
			FORCEINLINE IValue* GetValue() { return Value; }
			FORCEINLINE const IValue* GetValue() const { return Value; }
			FORCEINLINE const FECsDamageValue& GetType() const { return Type; }

			void CopyFrom(const FString& Context, UObject* InRoot, const IValue* From);

			#define DataType NCsDamage::NData::IData
			void CopyFrom(const FString& Context, UObject* InRoot, const DataType* Data);
			#undef DataType

			void CopyFrom(const FAllocated* From);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}