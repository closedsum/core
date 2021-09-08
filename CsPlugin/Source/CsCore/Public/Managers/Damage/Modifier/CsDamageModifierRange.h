// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

class ICsData_Damage;

// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NRange
		{
			/**
			* Interface to describe modifying a damage range (NCsDamage::NRange::IRange) from 
			*  a damage data (ICsData_Damage).
			*/
			struct CSCORE_API IRange : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				typedef NCsDamage::NRange::IRange RangeType;

			public:

				virtual ~IRange(){}

				/**
				* Modify the damage Range. This range is a copy of the DamageRange from Data.
				*
				* @param Data		The data from which the Range was copied. This serves
				*					as a type and a way to check if and how the Range should be modified.
				* @param Range		The copy of the DamageRange from Data to be modified.
				*					NOTE: This range is allocated and must be freed at end of use.
				*/
				virtual void Modify(ICsData_Damage* Data, RangeType* Range) = 0;
			};
		}
	}
}