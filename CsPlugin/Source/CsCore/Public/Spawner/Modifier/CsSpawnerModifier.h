// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
		struct CSCORE_API IModifier : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IModifier(){}
		};
	}
}