// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

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

			/**
			* Modifies the value InValue
			* 
			* return OutValue
			*/
			virtual float Modify(const float& InValue) const = 0;
		};
	}
}