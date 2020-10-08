// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsData_Damage;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NValue
		{
			/**
			* Interface to describe modifying a damage value (NCsDamage::NValue::IValue) from 
			*  a damage data (ICsData_Damage).
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
				* Modify the damage Value. This value is a copy of the DamageValue from Data.
				*
				* @param Data		The data from which the Value was copied. This serves
				*					as a type and a way to check if and how the Value should be modified.
				* @param Value		The copy of the DamageValue from Data to be modified.
				*					NOTE: This value is allocated and must be freed at end of use.
				*/
				virtual void Modify(ICsData_Damage* Data, ValueType* Value) = 0;
			};
		}
	}
}