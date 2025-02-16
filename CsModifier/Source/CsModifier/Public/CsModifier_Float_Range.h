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
			struct CSMODIFIER_API IRange : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~IRange(){}

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;
				};

			public:

				/**
				* Modifies the minimum value InValue
				* 
				* return OutValue
				*/
				virtual float ModifyMin(const float& InValue) const = 0;

				virtual const _::ApplicationType& GetMinApplication() const = 0;

				/**
				* Modifies the maximum value InValue
				*
				* return OutValue
				*/
				virtual float ModifyMax(const float& InValue) const = 0;

				virtual const _::ApplicationType& GetMaxApplication() const = 0;
			};
		}
	}
}

using CsFloatRangeModifierType = NCsModifier::NFloat::NRange::IRange;