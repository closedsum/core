// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsStatusEffect
{
	namespace NModifier
	{
		namespace NDamage
		{
			/**
			* Interface to describe modifying a damage object (NCsDamage::NValue::IValue or NCsDamage::NRange::IRange)
			*  from a status effect (ICsData_StatusEffect_Damage)
			*/
			struct CSSE_API IDamage : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IDamage() {}
			};
		}
	}
}