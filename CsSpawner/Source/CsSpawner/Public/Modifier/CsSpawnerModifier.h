// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsSpawner
{
	namespace NModifier
	{
		/**
		* Interface for describing a Modifier for a Spawner.
		* Modifiers usually alter existing stats, members, ... etc on an object.
		*  Spawner is an object that implements the interface: ICsSpawner.
		*/
		struct CSSPAWNER_API IModifier : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IModifier(){}
		};
	}
}