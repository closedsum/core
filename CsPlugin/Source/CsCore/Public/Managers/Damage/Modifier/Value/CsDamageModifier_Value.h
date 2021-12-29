// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NValue
		{
			/**
			* Interface to describe modifying a damage value (NCsDamage::NValue::IValue).
			*/
			struct CSCORE_API IValue : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				typedef NCsDamage::NValue::IValue ValueType;

			public:

				virtual ~IValue(){}

				/**
				* Modify the damage Value.
				*
				* @param Value
				*/
				virtual void Modify(ValueType* Value) = 0;
			};
		}
	}
}