// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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