// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#pragma once

namespace NCsUserWidget
{
	namespace NCache
	{
		/**
		* Cache associated with an UserWidget
		*  The Manager for UserWidget primarily interacts with the Cache object in terms
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