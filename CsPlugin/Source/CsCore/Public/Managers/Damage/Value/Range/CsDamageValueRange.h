// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			/**
			* 
			*/
			struct CSCORE_API IRange : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

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