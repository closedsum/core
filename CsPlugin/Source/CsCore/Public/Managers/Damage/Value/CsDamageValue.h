// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
		/**
		* 
		*/
		struct CSCORE_API IValue : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IValue(){}
		};
	}
}