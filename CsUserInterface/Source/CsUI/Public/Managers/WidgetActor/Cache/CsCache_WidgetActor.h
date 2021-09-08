// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"

#pragma once

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