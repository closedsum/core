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
		/**
		* Interface for describing a Modifier for a Float value.
		* Modifiers usually alter existing stats, members, ... etc on an object.
		*/
		struct CSMODIFIER_API IFloat : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IFloat(){}

		private:

			// Allow clearer names without name collisions
			struct _
			{
				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;
			};

		public:

			/**
			* Modifies the value InValue
			* 
			* return OutValue
			*/
			virtual float Modify(const float& InValue) const = 0;

			virtual const _::ApplicationType& GetApplication() const = 0;
		};
	}
}

using CsFloatModifierType = NCsModifier::NFloat::IFloat;