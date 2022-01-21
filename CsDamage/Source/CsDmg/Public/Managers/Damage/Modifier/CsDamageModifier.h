// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsDamage
{
	namespace NModifier
	{
		/**
		* Interface to describe modifying a damage object (NCsDamage::NValue::IValue or NCsDamage::NRange::IRange)
		*  from a damage expression (ICsData_Damage)
		*/
		struct CSDMG_API IModifier : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IModifier(){}
		};
	}
}