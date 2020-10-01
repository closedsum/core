// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
#pragma once

class UObject;
struct FCsResource_DamageValue;

namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

namespace NCsDamage
{
	namespace NValue
	{
		/**
		* Container for an allocated object which implements the interface
		* NCsDamage::NValue::IValue. This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSCORE_API FAllocated
		{
		public:

			UObject* Root;

			FCsResource_DamageValue* Container;

			IValue* Value;

			FECsDamageValue Type;

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Value(nullptr),
				Type()
			{
			}

			FORCEINLINE const IValue* GetValue() const
			{
				return Value;
			}

			void CopyFrom(UObject* InRoot, const IValue* From);

			void CopyFrom(const FAllocated* From);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}