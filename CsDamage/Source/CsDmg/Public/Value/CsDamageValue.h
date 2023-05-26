// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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