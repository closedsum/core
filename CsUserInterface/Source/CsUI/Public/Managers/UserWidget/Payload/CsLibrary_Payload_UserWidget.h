// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
// Container
#include "Containers/CsLibrary_InterfaceMap.h"

namespace NCsUserWidget
{
	namespace NPayload
	{
		namespace NLibrary
		{
			using PayloadType = NCsUserWidget::NPayload::IPayload;

			/**
			*/
			struct CSUI_API FLibrary final : public NCsInterfaceMap::TLibrary<PayloadType>
			{
			public:
			};
		}
	}
}