// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Macro/CsMacro_Namespace.h"

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsDamage
{
	namespace NValue
	{
		namespace NCopy
		{
			/**
			* Interface for a Damage Value, object that implements the interface: NCsDamage::NValue::IValue,
			* performing various Copy commands.
			*/
			struct CSDMG_API ICopy : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define ValueType NCsDamage::NValue::IValue

			public:

				virtual ~ICopy(){}

				virtual void Copy(const ValueType* From) = 0;

			#undef ValueType
			};
		}
	}
}