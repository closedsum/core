// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsData_StatusEffect_Damage;

namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

namespace NCsStatusEffect
{
	namespace NModifier
	{
		namespace NDamage
		{
			/**
			* Interface to describe modifying a damage range (ICsDamageRange) from 
			*  a status effect (ICsData_StatusEffect_Damage).
			*/
			struct CSSE_API IDamageRange : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IDamageRange() {}

			private:

				typedef NCsDamage::NRange::IRange DamageRangeType;

			public:

				/**
				* Modify the damage Range. This range is a copy of the DamageRange from Data,
				* which implements the interface ICsData_StatusEffect_Damage.
				*
				* @param Data	The data from which the Range was copied. This serves
				*				as a type and a way to check if and how the Range should be modified.
				* @param Range	The copy of the DamageRange from Data, which implements the interface:
								ICsData_StatusEffect_Damage, to be modified.
				*				NOTE: This range is allocated and must be freed at end of use.
				*/
				virtual void Modify(ICsData_StatusEffect_Damage* Data, DamageRangeType* Range) = 0;
			};
		}
	}
}