// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsDamage
{
	namespace NValue
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

				/**
				* Get the minimum value.
				*
				* return Minimum Value.
				*/
				virtual const float& GetMinValue() const = 0;

				/**
				* Get the maximum value.
				*
				* return Maximum Value.
				*/
				virtual const float& GetMaxValue() const = 0;
			};
		}
	}
}