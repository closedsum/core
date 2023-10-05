// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Payload/CsTypes_Payload_UserWidget.h"
#include "CsUI.h"

// UserWidgetPayload
#pragma region

namespace NCsUserWidgetPayload
{
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(UserWidget, "NCsUserWidget::NPayload::IPayload");
	CSUI_API CS_CREATE_ENUM_STRUCT_CUSTOM(Text, "NCsUserWidget::NPayload::NText::IText");
}

#pragma endregion UserWidgetPayload