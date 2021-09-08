// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsData_StatusEffect_Damage;

namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

namespace NCsStatusEffect
{
	namespace NModifier
	{
		namespace NDamage
		{
			/**
			* Interface to describe modifying a damage value (NCsDamage::NValue::IValue) from 
			*  a status effect (ICsData_DamageStatus_Damage).
			*/
			struct CSSE_API IDamageValue : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IDamageValue() {}

			private:

				typedef NCsDamage::NValue::IValue DamageValueType;

			public:

				/**
				* Modify the damage Value. This value is a copy of the DamageValue from Data,
				* which implements the interface ICsData_StatusEffect_Damage.
				*
				* @param Data	The Data from which the Value was copied. This serves
				*				as a type and a way to check if and how the Value should be modified.
				* @param Value	The copy of the DamageValue from Data, which implements the interface:
								ICsData_StatusEffect_Damage, to be modified.
				*				NOTE: This value is allocated and must be freed at end of use.
				*/
				virtual void Modify(ICsData_StatusEffect_Damage* StatusEffect, DamageValueType* Value) = 0;
			};
		}
	}
}