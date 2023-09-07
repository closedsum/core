// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsDamage
{
	namespace NRange
	{
		/**
		* 
		*/
		struct CSDMG_API IRange : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IRange(){}

			virtual const float& GetMinRange() const = 0;

			virtual const float& GetMaxRange() const = 0;
		};
	}
}