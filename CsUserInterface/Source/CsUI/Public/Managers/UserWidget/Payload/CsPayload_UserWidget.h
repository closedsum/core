// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Components/SlateWrapperTypes.h"
#pragma once

namespace NCsUserWidget
{
	namespace NPayload
	{
		/**
		*/
		struct CSUI_API IPayload : virtual public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload(){}

			virtual const ESlateVisibility& GetVisibility() const = 0;
		};
	}
}