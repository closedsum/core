// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Modifier/CsTypes_Modifier.h"

namespace NCsModifier
{
	namespace NFloat
	{
		/**
		* Interface for describing a Modifier for a Float value.
		* Modifiers usually alter existing stats, members, ... etc on an object.
		*/
		struct CSCORE_API IFloat : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IFloat(){}

		#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

			/**
			* Modifies the value InValue
			* 
			* return OutValue
			*/
			virtual float Modify(const float& InValue) const = 0;

			virtual const ApplicationType& GetApplication() const = 0;

		#undef ApplicationType
		};
	}
}