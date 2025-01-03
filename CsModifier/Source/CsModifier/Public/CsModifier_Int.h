// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsModifier
{
	namespace NInt
	{
		/**
		* Interface for describing a Modifier for a Int value.
		* Modifiers usually alter existing stats, members, ... etc on an object.
		*/
		struct CSMODIFIER_API IInt : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IInt(){}

			/**
			* Modifies the value InValue
			* 
			* return OutValue
			*/
			virtual int32 Modify(const int32& InValue) const = 0;
		};
	}
}

using CsIntModifierType = NCsModifier::NInt::IInt;