// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
		/**
		* 
		*/
		struct CSCORE_API IValue : virtual public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:
		};
	}
}