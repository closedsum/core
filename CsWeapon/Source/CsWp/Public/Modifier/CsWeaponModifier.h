// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class ICsWeapon;

namespace NCsWeapon
{
	namespace NModifier
	{
		/**
		* Interface for describing a Modifier for a Weapon.
		* Modifiers usually alter existing stats, members, ... etc on an object.
		*  Weapon is an object that implements the interface: ICsWeapon.
		*/
		struct CSWP_API IModifier : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IModifier() {}
		};
	}
}