// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"

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