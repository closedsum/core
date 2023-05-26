// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsModifier
{
	namespace NInt
	{
		namespace NRange
		{
			/**
			* Interface for describing a Modifier for a Int value with Min and Max values.
			* Modifiers usually alter existing stats, members, ... etc on an object.
			*/
			struct CSCORE_API IRange : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IRange(){}

				/**
				* Modifies the minimum value InValue
				* 
				* return OutValue
				*/
				virtual int32 ModifyMin(const int32& InValue) const = 0;

				/**
				* Modifies the maximum value InValue
				*
				* return OutValue
				*/
				virtual int32 ModifyMax(const int32& InValue) const = 0;
			};
		}
	}
}