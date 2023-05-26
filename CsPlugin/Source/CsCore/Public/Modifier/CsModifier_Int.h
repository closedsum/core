// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
		struct CSCORE_API IInt : public ICsGetInterfaceMap
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