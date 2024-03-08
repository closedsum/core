// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class UCsWidgetComponent;

namespace NCsWidgetActor
{
	namespace NCache
	{
		/**
		* Cache associated with an object that implements the interface: ICsWidgetActor
		*  The Manager for Widget Actor primarily interacts with the Cache object in terms
		*  of allocation and deallocation.
		*/
		struct CSUI_API ICache : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~ICache() {}
		};
	}
}