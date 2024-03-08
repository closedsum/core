// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsTypes_Modifier.h"

namespace NCsModifier
{
	namespace NFloat
	{
		namespace NRange
		{
			/**
			* Interface for describing a Modifier for a Float value with Min and Max values.
			* Modifiers usually alter existing stats, members, ... etc on an object.
			*/
			struct CSMODIFY_API IRange : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IRange(){}

			#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

				/**
				* Modifies the minimum value InValue
				* 
				* return OutValue
				*/
				virtual float ModifyMin(const float& InValue) const = 0;

				virtual const ApplicationType& GetMinApplication() const = 0;

				/**
				* Modifies the maximum value InValue
				*
				* return OutValue
				*/
				virtual float ModifyMax(const float& InValue) const = 0;

				virtual const ApplicationType& GetMaxApplication() const = 0;

			#undef ApplicationType
			};
		}
	}
}