// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsDamage
{
	namespace NValue
	{
		/**
		* 
		*/
		struct CSDMG_API IValue : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IValue(){}
		};
	}
}

using CsDamageValueType = NCsDamage::NValue::IValue;