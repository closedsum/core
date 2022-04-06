// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
// Container
#include "Containers/CsLibrary_InterfaceMap.h"

namespace NCsUserWidget
{
	namespace NPayload
	{
	#define PayloadType NCsUserWidget::NPayload::IPayload

		/**
		*/
		struct CSUI_API FLibrary final : public NCsInterfaceMap::TLibrary<PayloadType>
		{
		public:
		};

	#undef PayloadType
	}
}