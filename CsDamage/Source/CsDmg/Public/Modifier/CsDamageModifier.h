// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

namespace NCsDamage
{
	namespace NModifier
	{
		/**
		* Interface to describe modifying a damage object (ValueType: NCsDamage::NValue::IValue or 
		*  RangeType: NCsDamage::NRange::IRange) from a damage expression (ICsData_Damage)
		*/
		struct CSDMG_API IModifier : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IModifier(){}

			/**
			* Get the set of Damage Datas (by Type) the Modifier applies to.
			* If the set is EMPTY, the Modifier applies to all Damage Datas.
			* 
			* return Set
			*/
			virtual const TSet<FECsDamageData>& GetWhitelistByDataTypeSet() const = 0;
		};
	}
}

using CsDamageModifierType = NCsDamage::NModifier::IModifier;