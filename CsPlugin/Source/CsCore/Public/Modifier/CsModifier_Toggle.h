// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsModifier
{
	namespace NToggle
	{
		/**
		* Interface for describing a Modifier for enable / disabling a property.
		* Modifiers usually alter existing stats, members, ... etc on an object.
		*/
		struct CSCORE_API IToggle : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IToggle(){}

			/**
			* Get whether the Property associated with this Modifier is enable or not
			* 
			* return
			*/
			virtual bool IsEnabled() const = 0;
		};
	}
}